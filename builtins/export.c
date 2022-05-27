/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 11:40:39 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/27 20:40:31 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	replace_env(char *export, char **envp, int index)
{
	int	equals_index;

	equals_index = 0;
	while (export[equals_index] && export[equals_index] != '=')
		equals_index++;
	free(envp[index]);
	envp[index] = ft_strdup(export);
	if (!envp[index])
		return (1);
	return (0);
}

int	realloc_env(t_data *data, int new_exports)
{
	char	**old_envp;
	char	**new_envp;
	int		i;

	i = 0;
	while (data->envp && data->envp[i])
		i++;
	new_envp = ft_calloc(i + new_exports, sizeof(char *));
	if (!new_envp)
		return (1);
	i = 0;
	while (data->envp && data->envp[i])
	{
		new_envp[i] = data->envp[i];
		i++;
	}
	old_envp = data->envp;
	data->envp = new_envp;
	free(old_envp);
	return (0);
}

int	addto_env(char **cmd, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (envp[i])
		i++;
	while (cmd[j] && is_valid(cmd[j]) > 0)
	{
		if (is_set(cmd[j], envp) == -1)
		{
			envp[i] = ft_strdup(cmd[j]);
			if (!envp[i])
				return (1);
		}
		i++;
		j++;
	}
	return (0);
}

char	*dollar_trim(char *cmd)
{
	char			*trim;
	unsigned int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '$')
		i++;
	if (i == ft_strlen(cmd))
		return (cmd);
	trim = malloc(i + 1);
	if (!trim)
		return (NULL);
	i = 0;
	while (cmd[i] && cmd[i] != '$')
	{
		trim[i] = cmd[i];
		i++;
	}
	trim[i] = 0;
	free(cmd);
	return (trim);
}

int	builtin_export(char **cmd, t_data *data)
{
	int	i;
	int	index;

	i = 1;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		cmd[i] = dollar_trim(cmd[i]);
		if (!cmd[i])
			internal_error_return(ERROR_MALLOC);
		index = is_set(cmd[i], data->envp);
		if (index == -2)
			return (put_error(SHELLNAME, cmd[0], cmd[i], "not a valid identifier"));
		if (ft_strncmp(cmd[i], "_=", 2) && ft_strchr(cmd[i], '=') != 0)
		{
			if (index >= 0 && replace_env(cmd[i], data->envp, index) != 0)
				return (error_return("export", NULL, 1, 0));
		}
		i++;
	}
	if (realloc_env(data, i) != 0 || addto_env(cmd, data->envp) != 0)
		return (error_return("export", NULL, 1, 0));
	return (0);
}
