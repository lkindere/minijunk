/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:22:08 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/31 22:19:45 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Closes current commands in and out if not STD
int	close_fds(t_cmd *cmd, t_data *data)
{
	if (data)
		;
	if (cmd->in > 0 && close(cmd->in) == -1)
		internal_error_exit(ERROR_CLOSE);
	if (cmd->out > 1 && close(cmd->out) == -1)
		internal_error_exit(ERROR_CLOSE);
	if (cmd->pipe_next && cmd->pipe_next->in >= 0 && close(cmd->pipe_next->in) == -1)
		internal_error_exit(ERROR_CLOSE);

	return (1);
}

int	pipe_check(t_data *data, t_cmd *cmd, int end)
{
	if (end == 0)
	{
		if (cmd->in == 0)
			return (1);
		if (cmd->in == data->pipe1[0] || cmd->in == data->pipe2[0])
			return (1);
		return (0);
	}
	if (end == 1)
	{
		if (cmd->out == 1)
			return (1);
		if (cmd->out == data->pipe1[1] || cmd->out == data->pipe2[1])
			return (1);
		return (0);
	}
	return (-1);
}

//Creates pipes on cmd and cmd next
int	create_pipes(t_data *data, t_cmd *cmd)
{
	int	pfd[2];

	if (pipe(pfd) == -1)
		internal_error_exit(ERROR_PIPE);
	if (pipe_check(data, cmd, 1))
		cmd->out = pfd[1];
	else
		close (pfd[1]);
	if (pipe_check(data, cmd->pipe_next, 0))
		cmd->pipe_next->in = pfd[0];
	else
		close (pfd[0]);
	return (1);
}
