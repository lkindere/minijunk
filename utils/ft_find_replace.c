/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:07:27 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/23 18:18:26 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

//Iterates through the strings and replaces character c with r
//if d == 1 increments from 0 index, if d == -1 decrements from strlen
void    ft_find_replace(char *str, int c, int r, int d)
{
    int i;

    i = -1;
    if (d == -1)
    {
        i = ft_strlen(str);
        while (--i >= 0)
        {
            if (str[i] == c)
                str[i] = r;
        }
    }
    else if (d == 1)
    {
        while (str[++i])
        {
            if (str[i] == c)
                str[i] = r;
        }
    }
}
