/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 07:49:39 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 19:24:24 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int builtin_exit(t_cmd *cmd, t_data *data)
{
    if (!cmd && !data)
    {
        write(2, "\nexit D:\n", 9);
        exit (0);
    }
    if (cmd->cmd_arg[1])
        return (error_return(cmd->cmd_arg[0], "too many arguments", 0, 0));
    if (!cmd->pipe_next && !cmd->pipe_prev)
    {
        write(2, "exit D:\n", 9);
        exit (0);
    }
	return (0);
}
