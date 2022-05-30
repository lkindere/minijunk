/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:07:27 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/30 21:26:52 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static void	reverse(char *str, int c, int r, int d)
{
	int	i;

	i = ft_strlen(str);
	while (--i >= 0)
	{
		if (str[i] == c)
		{
			str[i] = r;
			return ;
		}
	}
}

//Iterates through the strings and replaces character c with r
//if d == 1 increments from 0 index, if d == -1 decrements from strlen
void	ft_find_replace(char *str, int c, int r, int d)
{
	int	i;

	i = -1;
	if (d == -1)
	{
		reverse(str, c, r, d);
		return ;
	}
	else if (d == 1)
	{
		while (str[++i])
		{
			if (str[i] == c)
			{
				str[i] = r;
				return ;
			}
		}
	}
}
