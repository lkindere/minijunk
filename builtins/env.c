/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:13:00 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/02 01:00:36 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Prints out the environment
int	builtin_env(char **envp, int fd)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
	{
		if (write(fd, envp[i], ft_strlen(envp[i])) == -1)
			return (1);
		if (write(fd, "\n", 1) == -1)
			return (1);
		i++;
	}
	return (0);
}
