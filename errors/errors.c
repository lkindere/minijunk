/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:49:51 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/30 06:53:04 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
 *	Prints error message to STDERR.
 *	If token is set, prints:
 *	<prompt>: <blank> error near unexpected token `<token'
 *	If token is NULL, prints:
 *	<prompt>: <blank> error
 */
int	blank_err(t_data *data, char *blank, char *token)
{
	(void)data;
	ft_putstr_fd(PROMPT": ", STDERR_FILENO);
	ft_putstr_fd(blank, STDERR_FILENO);
	if (token)
	{
		ft_putstr_fd(" error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(" error", STDERR_FILENO);
	}
	ft_putstr_fd("\'\n", STDERR_FILENO);
	exit_code(258);
	return (1);
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
