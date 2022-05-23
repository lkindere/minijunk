/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:12:14 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/19 23:17:07 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Updates pwd and writes it out
int	builtin_pwd(char *pwd, int fd)
{
	int		i;

	i = 0;
	pwd = getcwd(pwd, PATH_MAX);
	if (!pwd)
		return (error_return("pwd", NULL, 1, 0));
	while (pwd[i])
	{
		if (write(fd, &pwd[i++], 1) == -1)
			return (error_return("pwd", NULL, 1, 0));
	}
	if (write(fd, "\n", 1) == -1)
		return (error_return("pwd", NULL, 1, 0));
	return (0);
}
