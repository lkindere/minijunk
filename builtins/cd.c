/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:12:33 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 23:44:00 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	cd_home(char **cmd, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i] && ft_strncmp("HOME=", data->envp[i], 5))
		i++;
	if (!data->envp || !data->envp[i])
		return (error_return(cmd[0], "HOME not set", 0, 0));
	if (chdir(&data->envp[i][5]) == -1)
		return (error_return(cmd[0], NULL, 1, 0));
	return (0);
}

//cd's into first arg of cd, if no arg cd's to home dir
int	builtin_cd(char **cmd, t_data *data)
{
	if (!cmd[1])
	{
		if (!data->envp)
			return (error_return(cmd[0], "HOME not set", 0, 0));
		return (cd_home(cmd, data));
	}
	if (cmd[1])
	{
		if (cmd[2])
			return (error_return(cmd[0], "too many arguments", 0, 0));
		if (chdir(cmd[1]) == -1)
			return (error_return(cmd[0], cmd[1], 1, 0));
		data->pwd = getcwd(data->pwd, PATH_MAX);
		if (!data->pwd)
			return (error_return(cmd[0], NULL, 1, 0));
	}
	return (0);
}
