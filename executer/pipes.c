/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:22:08 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/30 16:50:34 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Closes current commands in and out if not STD
int	close_fds(t_cmd *cmd)
{
	if (cmd->in > 0 && close(cmd->in) == -1)
		internal_error_exit(ERROR_CLOSE);
	if (cmd->out > 1 && close(cmd->out) == -1)
		internal_error_exit(ERROR_CLOSE);
	return (1);
}

//Creates pipes on cmd and cmd next
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
