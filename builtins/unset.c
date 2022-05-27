/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:05:48 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/27 12:57:44 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Moves the env variable to the back of the list and sets it to NULL
static int	unset_env(t_data *data, int index)
{
	free(data->envp[index]);
	while (data->envp[index + 1])
	{
		data->envp[index] = data->envp[index + 1];
		index++;
	}
	data->envp[index] = NULL;
	return (0);
}

//Checks if builtin is set and calls unset
int	builtin_unset(char **cmd, t_data *data)
{
	char	*temp;
	int		index;
	int		i;

	i = 1;
	if (!cmd[i])
		return (0);
	while (cmd[i])
	{	
		temp = ft_strjoin(cmd[i], "=");
		if (!temp)
			internal_error_return(ERROR_MALLOC);
		if (ft_strcmp(temp, "_="))
			index = is_set(temp, data->envp);
		free(temp);
		if (index >= 0 && unset_env(data, index) != 0)
			return (error_return("unset", NULL, 1, 0));
		if (index == -2)
		{
			put_error(SHELLNAME, cmd[0], cmd[i], "not a valid identifier");
			data->exit_code = 1;
		}
		i++;
	}
	return (data->exit_code);
}
