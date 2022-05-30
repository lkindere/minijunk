/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:25:45 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/30 07:57:19 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

//Substring but appends c at the end
char	*ft_substr_append(char const *s, unsigned int start, size_t len, char c)
{
	char			*substr;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		substr = malloc(1);
		substr[0] = '\0';
		return (substr);
	}
	if (len < ft_strlen(&s[start]))
		substr = malloc(len + 2);
	else
		substr = malloc(ft_strlen(&s[start]) + 2);
	if (!substr)
		return (NULL);
	while (i < len && s[start])
		substr[i++] = s[start++];
	substr[i++] = c;
	substr[i] = 0;
	return (substr);
}
