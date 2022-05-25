/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:38:37 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 18:10:57 by lkindere         ###   ########.fr       */
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
void	create_pipes(t_cmd *cmd)
{
	int	pfd[2];

	if (pipe(pfd) == -1)
		internal_error_exit(ERROR_PIPE);
	cmd->out = pfd[1];
	cmd->pipe_next->in = pfd[0];
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
	if (is_exec && access(cmd->cmd_arg[0], F_OK) != 0)
		error_exit(cmd->cmd_arg[0], NULL, 1, 126);
	return (0 + is_exec);
}
