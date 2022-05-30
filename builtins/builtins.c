/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:37:53 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/30 20:50:18 by lkindere         ###   ########.fr       */
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
//Returns -1 if not found
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

//Checks if arg is a builtin
int	is_builtin(char *s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "pwd") || !ft_strcmp(s, "env"))
		return (1);
	if (!ft_strcmp(s, "export") || !ft_strcmp(s, "unset"))
		return (1);
	if (!ft_strcmp(s, "exit") || !ft_strcmp(s, "cd"))
		return (1);
	return (0);
}

//Checks if it can close the fds and closes them
static void	close_check(t_data *data, t_cmd *cmd, int end)
{
	if (end == 0)
	{
		if (cmd->in <= 0)
			return ;
		if (cmd->in == data->pipe1[0] || cmd->in == data->pipe2[0])
			return ;
		if (close(cmd->in) == -1)
			internal_error_return(ERROR_CLOSE);
	}
	if (end == 1)
	{
		if (cmd->out <= 1)
			return ;
		if (cmd->out == data->pipe1[1] || cmd->in == data->pipe2[1])
			return ;
		if (close(cmd->out) == -1)
			internal_error_return(ERROR_CLOSE);
	}
}

//Runs a builtin if it matches the command and sets it's exit code
//Returns 0 if not a builtin
//Returns 1 if builtin
int	check_builtin(t_data *data, t_cmd *cmd)
{
	if (!is_builtin(cmd->cmd_arg[0]))
		return (0);
	if (cmd->in > 0 && close(cmd->in) == -1)
		internal_error_return(ERROR_CLOSE);
	if (!ft_strcmp(cmd->cmd_arg[0], "echo"))
		exit_code(builtin_echo(cmd->cmd_arg, cmd->out));
	if (!ft_strcmp(cmd->cmd_arg[0], "pwd"))
		exit_code(builtin_pwd(data->pwd, cmd->out));
	if (!ft_strcmp(cmd->cmd_arg[0], "env"))
		exit_code(builtin_env(data->envp, cmd->out));
	if (!ft_strcmp(cmd->cmd_arg[0], "cd"))
		exit_code(builtin_cd(cmd->cmd_arg, data));
	if (!ft_strcmp(cmd->cmd_arg[0], "export"))
		exit_code(builtin_export(cmd->cmd_arg, data));
	if (!ft_strcmp(cmd->cmd_arg[0], "unset"))
		exit_code(builtin_unset(cmd->cmd_arg, data));
	if (!ft_strcmp(cmd->cmd_arg[0], "exit"))
		exit_code(builtin_exit(cmd, data));
	close_check(data, cmd, 1);
	if (cmd->pipe_next)
		close_check(data, cmd->pipe_next, 0);
	return (1);
}
