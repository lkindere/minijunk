/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:11:41 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 21:58:15 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Writes echo, if not -n writes a new line
int	builtin_echo(char **cmd, int fd)
{
	int	i;

	i = 1;
	if (!cmd[1] && (write(fd, "\n", 1) == -1))
		return (error_return("echo", NULL, 1, 0));
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
		i = 2;
	while (cmd[i])
	{	
		if (write(fd, cmd[i], ft_strlen(cmd[i])) == -1)
			return (error_return("echo", NULL, 1, 0));
		i++;
		if (cmd[i] && write(fd, " ", 1) == -1)
			return (error_return("echo", NULL, 1, 0));
	}
	if (cmd[1] && ft_strcmp(cmd[1], "-n"))
	{
		if (write(fd, "\n", 1) == -1)
			return (error_return("echo", NULL, 1, 0));
	}
	return (0);
}
