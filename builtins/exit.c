/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 07:49:39 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/01 17:56:41 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Returns last exit code
//If param is above -1 updates it
int	exit_code(int new)
{
	static int	exit_code = {0};

	if (new > -1)
	{
		// printf("Exit code set to: %d\n", exit_code);
		exit_code = new;
	}
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

long long	ft_atolol(const char *str)
{
	long long	num;
	int			neg;
	int			i;

	num = 0;
	neg = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (num * neg);
}

int	valid_exit(char *arg)
{
	long long	exit_long;
	int			i;

	i = 0;
	if (!arg[i])
		return (0);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	exit_long = ft_atolol(arg);
	if (exit_long > LONG_MAX)
		return (0);
	exit_long %= 256;
	exit(exit_long);
}

int	builtin_exit(t_cmd *cmd, t_data *data)
{
	if (!data || !cmd)
		exit(1);
	if (cmd->cmd_arg[1] && !valid_exit(cmd->cmd_arg[1]))
	{
		error_return(cmd->cmd_arg[0], "numeric argument required", 0, 255);
		terminator(&data);
		exit(255);
	}
	if (cmd->cmd_arg[1] && cmd->cmd_arg[2])
	{
		error_return(cmd->cmd_arg[0], "too many arguments", 0, 255);
		terminator(&data);
		exit(255);
	}
	terminator(&data);
	exit(exit_code(-1));
}
