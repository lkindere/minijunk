/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:38:37 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/30 07:15:09 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_exception(char *input)
{
	int	i;

	i = 0;
	if (input_is_empty(input)
		&& put_error(SHELLNAME, input, "command not found", NULL))
		return (1);
	if (input[0] == '.' && input_is_empty(&input[1])
		&& put_error(SHELLNAME, input, "command not found", NULL))
		return (1);
	while (input[i] && input[i] != '/')
		i++;
	if (input[i] == '/' && !input[i + 1] && access(input, F_OK) == 0
		&& put_error(SHELLNAME, input, "command not found", NULL))
		return (1);
	return (0);
}

//Waits for all the commands executed in current run
//Frees cmds, gets exit codes
static void	executer_finish(t_cmd *first_cmd)
{
	while (first_cmd)
	{
		if (first_cmd->pid > 0)
			exit_code(get_exitstatus(first_cmd->pid));
		first_cmd = first_cmd->pipe_next;
	}
}

//Is a fork, exits in case of error
//Gets the paths, finds commands
//Forks again for execve, exits with exit code
int	executer_subfork(t_data *data, t_cmd *cmd)
{
	if (is_exception(cmd->cmd_arg[0]))
		return (126);
	cmd->paths = get_paths(data->envp);
	if (is_exec(cmd) && exec_access(cmd) != 0)
		return (exit_code(-1));
	if (!is_exec(cmd))
		cmd->cmd_path = find_cmd(data, cmd->cmd_arg[0], cmd->paths);
	if (!cmd->cmd_path)
		return (exit_code(-1));
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
		if (check_builtin(data, cmd) != -1 && terminator(&data))
			exit(exit_code(-1));
		if (check_builtin_exec(data, cmd) != -1 && terminator(&data))
			exit(exit_code(-1));
		exit_code(executer_subfork(data, cmd));
		terminator(&data);
		exit(exit_code(-1));
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
	exit_code(executer_subfork(data, cmd));
	return (1);
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
		{
			if (cmd->pipe_next)
				create_pipes(cmd);
			executer_startfork(data, cmd);
		}
		cmd = cmd->pipe_next;
	}
	executer_finish(first_cmd);
}
