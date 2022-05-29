/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 07:49:39 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/29 04:36:20 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	terminator(t_data **rip)
{
	int		i;
	t_data	*data;

	i = 0;
	data = *rip;
	while (data->envp && data->envp[i])
		free(data->envp[i++]);
	free(data->envp);
	free(data->pwd);
	reset_mem(data);
	free(*rip);
}

int	builtin_exit(t_cmd *cmd, t_data *data)
{
	int	exit_code;

	if (!data || !cmd)
		exit(1);
	exit_code = data->exit_code;
	if (cmd->cmd_arg[1])
	{
		error_return(cmd->cmd_arg[0], "too many arguments", 0, 255);
		terminator(&data);
		exit(255);
	}
	terminator(&data);
	exit(exit_code);
}
