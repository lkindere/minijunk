/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:11:41 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/02 01:01:20 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	new_line(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		while (cmd[i][j + 2])
		{
			if (cmd[i][j + 2] != 'n')
				return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (i);
}

//Writes echo, if not -n writes a new line
int	builtin_echo(char **cmd, int fd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (cmd[1] && new_line(&cmd[i]) > 0)
		nl = 0;
	i += new_line(&cmd[1]);
	while (cmd[i])
	{	
		if (write(fd, cmd[i], ft_strlen(cmd[i])) == -1)
			return (1);
		i++;
		if (cmd[i] && write(fd, " ", 1) == -1)
			return (1);
	}
	if (nl && write(fd, "\n", 1) == -1)
		return (1);
	return (0);
}
