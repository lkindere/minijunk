/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:38:37 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/01 22:49:12 by lkindere         ###   ########.fr       */
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
		if (!cmd->cmd_arg)
			exit(0);
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
	printf("cmd arg: %p\n", cmd->cmd_arg[0]);
	if (!cmd->cmd_arg[0])
		return ;
	if (is_exception(cmd->cmd_arg[0]))
		return ;
	check_wildcards(data, cmd);
	if (check_builtin(data, cmd))
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
