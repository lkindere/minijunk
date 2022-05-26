/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:38:37 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 22:30:42 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Waits for cmd->pid and returns exit code
int	get_exitstatus(int pid)
{
	int	exitstatus;

	waitpid(pid, &exitstatus, 0);
	if (WIFEXITED(exitstatus))
	{
		exitstatus = WEXITSTATUS(exitstatus);
		return (exitstatus);
	}
	return (1);
}

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
void	executer_subfork(t_data *data, t_cmd *cmd)
{
	cmd->paths = get_paths(data->envp);
	if (is_exec(cmd))
		cmd->cmd_path = cmd->cmd_arg[0];
	if (!is_exec(cmd))
		cmd->cmd_path = find_cmd(cmd->cmd_arg[0], cmd->paths, data->pwd);
	free_paths(&cmd->paths);
	cmd->pid = fork();
	if (cmd->pid == -1)
		internal_error_exit(ERROR_FORK);
	if (cmd->pid == 0)
		dup_and_exec(cmd, data->envp);
	data->exit_code = get_exitstatus(cmd->pid);
	exit (data->exit_code);
}

//Creates pipes if needed
//Forks for subfork
static void	executer_startfork(t_data *data, t_cmd *cmd)
{
	if (cmd->pipe_next)
		create_pipes(cmd);
	cmd->pid = fork();
	if (cmd->pid == -1)
		internal_error_exit(ERROR_FORK);
	if (cmd->pid == 0)
	{
		if (check_builtin_exec(data, cmd) == -1)
			executer_subfork(data, cmd);
	}
	if (cmd->pid != 0)
	{	
		if (cmd->pipe_prev && cmd->in != 0 && close(cmd->in) == -1)
			internal_error_exit(ERROR_CLOSE);
		if (cmd->pipe_next && cmd->out != 1 && close(cmd->out) == -1)
			internal_error_exit(ERROR_CLOSE);
	}
	if (cmd->pid == 0)
		exit(0);
}

//Iterates through cmd if it's not built in, calls the startfork,
//Once it reaches the final pipe calls finish to wait and get the exit codes
void	executer(t_data *data, t_cmd *cmd)
{
	t_cmd	*first_cmd;

	first_cmd = cmd;
	while (cmd)
	{
		if (cmd->cmd_arg && !input_is_empty(cmd->cmd_arg[0]))
		{
			check_wildcards(data, cmd);
			if (check_builtin(data, cmd) == -1)
				executer_startfork(data, cmd);
		}
		cmd = cmd->pipe_next;
	}
	executer_finish(data, first_cmd);
	// printf("Exexc -> exit_code: %d\n", data->exit_code);
}
