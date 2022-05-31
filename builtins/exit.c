/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 07:49:39 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/31 15:33:55 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Returns last exit code
//If param is above -1 updates it
int	exit_code(int new)
{
	static int	exit_code = {0};

	if (new > -1)
		exit_code = new;
	return (exit_code);
}

//Frees data before exit
int	terminator(t_data **rip)
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
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_data *data)
{
	if (!data || !cmd)
		exit(1);
	if (cmd->cmd_arg[1])
	{
		error_return(cmd->cmd_arg[0], "too many arguments", 0, 255);
		terminator(&data);
		exit(255);
	}
	terminator(&data);
	exit(exit_code(-1));
}
