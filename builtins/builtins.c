/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:37:53 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 19:26:48 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Returns 0 if valid, -1 if not valid for export, 1 if not valid in general
int	is_valid(char *var)
{
	int	i;

	i = 1;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	if (var[i] != '=')
		return (-1);
	return (1);
}

//Checks if the env variable is valid and is already set
//if set returns index of it
int	is_set(char *var, char **envp)
{
	int	i;
	int	equals_index;

	i = 0;
	equals_index = 0;
	if (is_valid(var) == 0)
		return (-2);
	if (!envp)
		return (-1);
	while (var[equals_index] && var[equals_index] != '=')
		equals_index++;
	while (envp[i])
	{
		if (!ft_strncmp(var, envp[i], equals_index + 1))
			return (i);
		i++;
	}
	return (-1);
}

//Runs a builtin if it matches the command and returns it's exit code
//Returns -1 if not a builtin exec (FORK)
int	check_builtin_exec(t_data *data, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd_arg[0], "echo"))
	{
		data->exit_code = builtin_echo(cmd->cmd_arg, cmd->out);
		return (data->exit_code);
	}
	if (!ft_strcmp(cmd->cmd_arg[0], "pwd"))
	{
		data->exit_code = builtin_pwd(data->pwd, cmd->out);
		return (data->exit_code);
	}
	if (!ft_strcmp(cmd->cmd_arg[0], "env"))
	{
		data->exit_code = builtin_env(data->envp, cmd->out);
		return (data->exit_code);
	}
	return (-1);
}

//Runs a builtin if it matches the command and returns it's exit code
//Returns -1 if not a builtin exec (NO FORK)
int	check_builtin(t_data *data, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd_arg[0], "cd"))
	{
		data->exit_code = builtin_cd(cmd->cmd_arg, data);
		return (data->exit_code);
	}
	if (!ft_strcmp(cmd->cmd_arg[0], "export"))
	{
		data->exit_code = builtin_export(cmd->cmd_arg, data);
		return (data->exit_code);
	}
	if (!ft_strcmp(cmd->cmd_arg[0], "unset"))
	{
		data->exit_code = builtin_unset(cmd->cmd_arg, data);
		return (data->exit_code);
	}
	if (!ft_strcmp(cmd->cmd_arg[0], "exit"))
	{
		data->exit_code = builtin_exit(cmd, data);
		return (data->exit_code);
	}
	return (-1);
}
