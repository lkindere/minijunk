/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 07:49:39 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/27 13:04:46 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	builtin_exit(t_cmd *cmd, t_data *data)
{
	if (!cmd && !data)
	{
		// write(2, "\nexit D:", 9);
		exit (data->exit_code);
	}
	if (cmd->cmd_arg[1])
		exit(error_return(cmd->cmd_arg[0], "too many arguments", 0, 255));
	if (!cmd->pipe_next && !cmd->pipe_prev)
	{
		// write(2, "exit D:", 9);
		exit (data->exit_code);
	}
	return (0);
}
