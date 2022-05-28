/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stristr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:45:34 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/28 11:41:38 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

//Returns last matched character index (-1 on no match)
//Ignores w characters in s2
int	ft_strwstr(const char *haystack, const char *needle, int w)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	e;

	i = -1;
	j = 0;
	e = 0;
	if (needle[0] == '\0')
		return (-1);
	while (haystack[++i])
	{
		while (needle[j + e] == w)
			e++;
		if (!needle[j + e])
			return (i + j - 1);
		while (haystack[i + j] == needle[j + e])
		{
			j++;
			while (needle[j + e] == w)
				w++;
			if (!needle[j + e])
				return (i + j - 1);
		}
		j = 0;
		e = 0;
	}
	return (-1);
}
