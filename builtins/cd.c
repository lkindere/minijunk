/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:12:33 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/27 21:35:01 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	change_pwd(char **cmd, t_data *data)
{
	char	*new_pwd;
	int		i;

	new_pwd = NULL;
	i = is_set("PWD=", data->envp);
	if (i >= 0)
	{
		new_pwd = getcwd(new_pwd, 0);
		if (!new_pwd)
			return (error_return(cmd[0], NULL, 1, 0));
		free(data->envp[i]);
		data->envp[i] = ft_strjoin("PWD=", new_pwd);
		if (!data->envp[i])
			return (error_return(cmd[0], NULL, 1, 0));
		free(data->pwd);
		data->pwd = new_pwd;
	}
	return (0);
}

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
	return (change_pwd(cmd, data));
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
	}
	return (change_pwd(cmd, data));
}
