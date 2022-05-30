/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:53:54 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/30 21:13:30 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

/*
 *	strncmp but protected for NULL ptr input and differentiating between
 *	"eof" and "eof ".
 */
int	ft_strcmp_x(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (1);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s1[i] != s2[i])
		return (2);
	return (0);
}
