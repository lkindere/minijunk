/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stristr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:45:34 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/07 21:37:10 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

//Returns last matched character index (-1 on no match)
int	ft_stristr(const char *haystack, const char *needle)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return (-1);
	while (haystack[i])
	{
		while (haystack[i + j] == needle[j])
		{
			j++;
			if (!needle[j])
				return (i + j - 1);
		}
		j = 0;
		i++;
	}
	return (-1);
}
