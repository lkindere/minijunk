/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:38:37 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/01 17:24:43 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Check access rights, reroutes the in/out and executes command
void	dup_and_exec(t_cmd *cmd, char **envp)
{
	if (access(cmd->cmd_path, X_OK) != 0)
		error_exit(cmd->cmd_arg[0], NULL, 1, 126);
	if (cmd->in < 0 || cmd->out < 0)
		exit(1);
	if (cmd->in != STDIN_FILENO)
	{
		if (dup2(cmd->in, STDIN_FILENO) == -1)
			internal_error_exit(ERROR_DUP);
		if (close(cmd->in) == -1)
			internal_error_exit(ERROR_CLOSE);
	}
	if (cmd->out != STDOUT_FILENO)
	{
		if (dup2(cmd->out, STDOUT_FILENO) == -1)
			internal_error_exit(ERROR_DUP);
		if (close(cmd->out) == -1)
			internal_error_exit(ERROR_CLOSE);
	}
	execve(cmd->cmd_path, cmd->cmd_arg, envp);
	error_exit(cmd->cmd_arg[0], NULL, 1, 0);
}

//Waits for all the commands executed in current run
//Frees cmds, gets exit codes
void	executer_finish(t_cmd *first_cmd)
{
	while (first_cmd)
	{
		for (int i = 3; i < 20; i++)
		{
			close(i);
		}
		if (first_cmd->in > STDIN_FILENO)
			close(first_cmd->in);
		if (first_cmd->out > STDOUT_FILENO)
			close(first_cmd->out);
		if (first_cmd->pid > 0)
			exit_code(get_exitstatus(first_cmd->pid));
		first_cmd = first_cmd->pipe_next;
	}
}

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

//Closes the forked process freeing everything in case of errors
int	fork_exit(t_data **data, t_cmd *cmd, int status)
{
	if (cmd->cmd_path != cmd->cmd_arg[0])
		free(cmd->cmd_path);
	cmd->cmd_path = NULL;
	// close_fds(cmd, *data);
	terminator(data);
	if (status >= 0)
		exit(status);
	exit(exit_code(-1));
}
