/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:54:56 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 19:55:13 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
