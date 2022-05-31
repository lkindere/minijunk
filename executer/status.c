/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:23:45 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/31 13:29:45 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

//Just weird exit codes
int	is_exception(char *input)
{
	int	i;

	i = 0;
	if (input_is_empty(input)
		&& put_error(SHELLNAME, input, "command not found", NULL))
	{
		exit_code(127);
		return (1);
	}
	if ((input[0] == '.' && input_is_empty(&input[1]))
		|| (input[1] == '.' && input_is_empty(&input[2])))
	{
		put_error(SHELLNAME, input, "command not found", NULL);
		exit_code(127);
		return (1);
	}
	while (input[i] && input[i] != '/')
		i++;
	if (input[i] == '/' && !input[i + 1] && access(input, F_OK) == 0
		&& put_error(SHELLNAME, input, "command not found", NULL))
	{
		exit_code(126);
		return (1);
	}
	return (0);
}

//Checks for correct exit code if executable fails
int	exec_access(t_cmd *cmd)
{
	if (access(cmd->cmd_arg[0], F_OK != 0))
	{
		if (errno == 20)
		{
			exit_code(126);
			return (error_return(cmd->cmd_arg[0], NULL, 1, 126));
		}
		exit_code(127);
		return (error_return(cmd->cmd_arg[0], NULL, 1, 127));
	}
	return (0);
}
