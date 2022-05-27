/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:38:37 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/27 21:58:43 by lkindere         ###   ########.fr       */
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

//Creates the pipes
//Returns 1
int	create_pipes(t_cmd *cmd)
{
	int	pfd[2];

	if (pipe(pfd) == -1)
		internal_error_exit(ERROR_PIPE);
	if (cmd->out == STDOUT_FILENO)
		cmd->out = pfd[1];
	else
		close (pfd[1]);
	if (cmd->pipe_next->in == STDIN_FILENO)
		cmd->pipe_next->in = pfd[0];
	else
		close (pfd[0]);
	return (1);
}

//Checks whether cmd is exec or command if exec doesn't exist error exits
int	is_exec(t_cmd *cmd)
{
	int	is_exec;
	int	i;

	is_exec = 0;
	i = 0;
	while (cmd->cmd_arg[0][i])
	{
		if (cmd->cmd_arg[0][i] == '/' && cmd->cmd_arg[0][i + 1])
			is_exec = 1;
		i++;
	}
	if (i > 0 && cmd->cmd_arg[0][i - 1] == '/')
		is_exec = 1;
	if (is_exec)
		cmd->cmd_path = cmd->cmd_arg[0];
	return (0 + is_exec);
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

//Checks for correct exit code if executable fails
int	exec_access(t_data *data, t_cmd *cmd)
{
	if (access(cmd->cmd_arg[0], F_OK != 0))
	{
		if (errno == 20)
		{
			data->exit_code = 126;
			return (error_return(cmd->cmd_arg[0], NULL, 1, 126));
		}
		data->exit_code = 127;
			return (error_return(cmd->cmd_arg[0], NULL, 1, 127));
	}
	return (0);
}