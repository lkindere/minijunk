/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_std.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:45:31 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/19 22:47:17 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	in_out_std(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	while (cmd)
	{
		if (cmd->in == -2)
			cmd->in = 0;
		if (cmd->out == -2)
			cmd->out = 1;
		cmd = cmd->pipe_next;
	}
}
