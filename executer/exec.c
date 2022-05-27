/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:38:37 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/27 15:08:36 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Waits for all the commands executed in current run
//Frees cmds, gets exit codes
static void	executer_finish(t_data *data, t_cmd *first_cmd)
{
	while (first_cmd)
	{
		if (first_cmd->pid > 0)
			data->exit_code = get_exitstatus(first_cmd->pid);
		first_cmd = first_cmd->pipe_next;
	}
}

//Is a fork, exits in case of error
//Gets the paths, finds commands
//Forks again for execve, exits with exit code
int	executer_subfork(t_data *data, t_cmd *cmd)
{
	cmd->paths = get_paths(data->envp);
	if (is_exec(cmd) && exec_access(data, cmd) != 0)
		return (data->exit_code);
	if (!is_exec(cmd))
		cmd->cmd_path = find_cmd(data, cmd->cmd_arg[0], cmd->paths);
	if (!cmd->cmd_path)
		return (data->exit_code);
	cmd->pid = fork();
	if (cmd->pid == -1)
		internal_error_exit(ERROR_FORK);
	if (cmd->pid == 0)
		dup_and_exec(cmd, data->envp);
	if (cmd->cmd_path != cmd->cmd_arg[0])
		free(cmd->cmd_path);
	cmd->cmd_path = NULL;
	return (get_exitstatus(cmd->pid));
}

//Creates pipes if needed
//Forks for subfork
static void	executer_startfork(t_data *data, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		internal_error_exit(ERROR_FORK);
	if (cmd->pid == 0)
	{
		check_wildcards(data, cmd);
		if (check_builtin(data, cmd) != -1)
			exit(data->exit_code);
		if (check_builtin_exec(data, cmd) != -1)
			exit(data->exit_code);
		data->exit_code = executer_subfork(data, cmd);
		exit(data->exit_code);
	}
	if (cmd->pid != 0)
	{	
		if (cmd->pipe_prev && cmd->in != 0 && close(cmd->in) == -1)
			internal_error_exit(ERROR_CLOSE);
		if (cmd->pipe_next && cmd->out != 1 && close(cmd->out) == -1)
			internal_error_exit(ERROR_CLOSE);
	}
}

//Returns 1
int	executer_main(t_data *data, t_cmd *cmd)
{
	check_wildcards(data, cmd);
	if (check_builtin(data, cmd) != -1)
		return (1);
	if (check_builtin_exec(data, cmd) != -1)
		return (1);
	data->exit_code = executer_subfork(data, cmd);
	return (1);
}

//Iterates through cmd if it's not built in, calls the startfork,
//Once it reaches the final pipe calls finish to wait and get the exit codes
void	executer(t_data *data, t_cmd *cmd)
{
	t_cmd	*first_cmd;

	first_cmd = cmd;
	if (!cmd->pipe_next && executer_main(data, cmd))
		return ;
	while (cmd)
	{
		if (cmd->cmd_arg && !input_is_empty(cmd->cmd_arg[0]))
		{
			if (cmd->pipe_next)
				create_pipes(cmd);
			executer_startfork(data, cmd);
		}
		cmd = cmd->pipe_next;
	}
	executer_finish(data, first_cmd);
}
