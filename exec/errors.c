/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:49:51 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/22 10:34:08 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	put_error(char *a, char *b, char *c, char *d)
{
	if (a)
	{
		write(STDERR_FILENO, a, ft_strlen(a));
		if (b || c || d)
			write(STDERR_FILENO, ": ", 2);
	}
	if (b)
	{
		write(STDERR_FILENO, b, ft_strlen(b));
		if (c || d)
			write(STDERR_FILENO, ": ", 2);
	}
	if (c)
	{
		write(STDERR_FILENO, c, ft_strlen(c));
		if (d)
			write(STDERR_FILENO, ": ", 2);
	}
	if (d)
		write(STDERR_FILENO, d, ft_strlen(d));
	write (STDERR_FILENO, "\n", 1);
}

//Prints out error and exits
int	error_exit(char *cmd, char *arg, int error, int exitcode)
{
	if (cmd && arg && error)
		put_error(SHELLNAME, cmd, arg, strerror(errno));
	if (cmd && !arg && error)
		put_error(SHELLNAME, cmd, strerror(errno), NULL);
	if (cmd && arg && !error)
		put_error(SHELLNAME, cmd, arg, NULL);
	if (exitcode != 0)
		exit(exitcode);
	exit(1);
}

//Prints out error and returns
int	error_return(char *cmd, char *arg, int error, int exitcode)
{
	if (cmd && arg && error)
		put_error(SHELLNAME, cmd, arg, strerror(errno));
	if (cmd && !arg && error)
		put_error(SHELLNAME, cmd, strerror(errno), NULL);
	if (cmd && arg && !error)
		put_error(SHELLNAME, cmd, arg, NULL);
	if (exitcode != 0)
		return (exitcode);
	return (1);
}

//Prints out a custom error and exits
void	internal_error_exit(t_error error)
{
	if (error == ERROR_NULL)
		put_error("Internal error: NULL", NULL, NULL, NULL);
	if (error == ERROR_MALLOC)
		put_error("Internal error: malloc failure", NULL, NULL, NULL);
	if (error == ERROR_FORK)
		put_error("Internal error: fork failure", NULL, NULL, NULL);
	if (error == ERROR_PIPE)
		put_error("Internal error: pipe failure", NULL, NULL, NULL);
	if (error == ERROR_DUP)
		put_error("Internal error: dup failure", NULL, NULL, NULL);
	if (error == ERROR_CLOSE)
		put_error("Internal error: close failure", NULL, NULL, NULL);
	if (error == ERROR_EXEC)
		put_error("Internal error: execve failure", NULL, NULL, NULL);
	exit (1);
}

//Prints out a custom error and returns
int	internal_error_return(t_error error)
{
	if (error == ERROR_NULL)
		put_error("Internal error: NULL\n", NULL, NULL, NULL);
	if (error == ERROR_MALLOC)
		put_error("Internal error: malloc failure\n", NULL, NULL, NULL);
	if (error == ERROR_FORK)
		put_error("Internal error: fork failure\n", NULL, NULL, NULL);
	if (error == ERROR_PIPE)
		put_error("Internal error: pipe failure\n", NULL, NULL, NULL);
	if (error == ERROR_DUP)
		put_error("Internal error: dup failure\n", NULL, NULL, NULL);
	if (error == ERROR_CLOSE)
		put_error("Internal error: close failure\n", NULL, NULL, NULL);
	if (error == ERROR_EXEC)
		put_error("Internal error: execve failure\n", NULL, NULL, NULL);
	return (1);
}
