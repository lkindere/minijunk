/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:38:37 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/01 17:58:01 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Gets data and calls execve
static void	executer_subfork(t_data *data, t_cmd *cmd)
{
	if (is_exception(cmd->cmd_arg[0]))
		fork_exit(&data, cmd, exit_code(-1));
	cmd->paths = get_paths(data->envp);
	if (is_exec(cmd) && exec_access(cmd) != 0)
		fork_exit(&data, cmd, -1);
	if (!is_exec(cmd))
		cmd->cmd_path = find_cmd(data, cmd->cmd_arg[0], cmd->paths);
	if (!cmd->cmd_path)
		fork_exit(&data, cmd, -1);
	signal_default();
	dup_and_exec(cmd, data->envp);
	fork_exit(&data, cmd, -1);
}

//Creates pipes on cmd and cmd next
int	create_pipes(t_data *data, t_cmd *cmd)
{
	int	pfd[2];

	(void)data;
	if (pipe(pfd) == -1)
		internal_error_exit(ERROR_PIPE);
	if (cmd->out != STDOUT_FILENO)
		close(pfd[1]);
	if (cmd->out == STDOUT_FILENO)
		cmd->out = pfd[1];
	if (cmd->pipe_next->in != STDIN_FILENO)
		close(pfd[0]);
	if (cmd->pipe_next->in == STDIN_FILENO)
		cmd->pipe_next->in = pfd[0];
	return (0);
}

void	close_sub(t_cmd *cmd)
{
	if (cmd->pipe_next)
	{
		if (cmd->pipe_next->in != STDIN_FILENO)
			close(cmd->pipe_next->in);
	}
}

void	close_main(t_cmd *cmd)
{
	if (cmd->in != STDIN_FILENO)
		close(cmd->in);
	if (cmd->out != STDOUT_FILENO)	
		close(cmd->out);
}

//Starting fork for piping
static void	executer_startfork(t_data *data, t_cmd *cmd)
{
	if (cmd->pipe_next)
		create_pipes(data, cmd);
	cmd->pid = fork();
	if (cmd->pid == -1)
		internal_error_exit(ERROR_FORK);
	if (cmd->pid == 0)
	{
		close_sub(cmd);
		check_wildcards(data, cmd);
		if (check_builtin(data, cmd) && terminator(&data))
			exit(exit_code(-1));
		executer_subfork(data, cmd);
	}
	if (cmd->pid != 0)
		close_main(cmd);

}

//Forks for execve on main
static void	main_subfork(t_data *data, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		internal_error_exit(ERROR_FORK);
	if (cmd->pid == 0)
	{
		signal_default();
		dup_and_exec(cmd, data->envp);
	}
	if (cmd->cmd_path != cmd->cmd_arg[0])
		free(cmd->cmd_path);
	cmd->cmd_path = NULL;
	close_main(cmd);
	exit_code(get_exitstatus(cmd->pid));
}

//Main if no pipes, prepares data and calls subfork
static void	executer_main(t_data *data, t_cmd *cmd)
{
	check_wildcards(data, cmd);
	if (check_builtin(data, cmd))
		return ;
	if (is_exception(cmd->cmd_arg[0]))
		return ;
	cmd->paths = get_paths(data->envp);
	if (is_exec(cmd) && exec_access(cmd) != 0)
		return ;
	if (!is_exec(cmd))
		cmd->cmd_path = find_cmd(data, cmd->cmd_arg[0], cmd->paths);
	if (!cmd->cmd_path)
		return ;
	main_subfork(data, cmd);
}

//Iterates through cmd if it's not built in, calls the startfork,
//Once it reaches the final pipe calls finish to wait and get the exit codes
void	executer(t_data *data, t_cmd *cmd)
{
	t_cmd	*first_cmd;

	first_cmd = cmd;
	if (!cmd->pipe_next)
	{
		if (cmd->in != -1 && cmd->out != -1 && cmd->cmd_arg)
			executer_main(data, cmd);
		return ;
	}
	while (cmd)
	{
		if (cmd->in != -1 && cmd->out != -1 && cmd->cmd_arg)
			executer_startfork(data, cmd);
		cmd = cmd->pipe_next;
	}
	executer_finish(first_cmd);
}
