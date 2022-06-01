/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 21:15:28 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/02 00:59:25 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Creates pipes on cmd and cmd next
int	create_pipes(t_data *data, t_cmd *cmd)
{
	int	pfd[2];

	(void)data;
	if (pipe(pfd) == -1)
		internal_error_exit(ERROR_PIPE);
	if (cmd->out != STDOUT_FILENO || cmd->in == -1)
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
