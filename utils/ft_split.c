/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:03:47 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 23:47:09 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	word_count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static char	*fill_arrays(const char *s, char c, int	*first)
{
	char	*str;
	int		i;
	int		last;

	i = 0;
	while (s[*first] == c && s[*first])
		(*first)++;
	last = *first;
	while (s[last] != c && s[last])
		(last)++;
	str = malloc((last - *first) + 1);
	if (!str)
		return (NULL);
	while (*first < last)
	{
		str[i] = s[*first];
		(*first)++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**splitter(char const *s, char c, int *first, int *wcount)
{
	int		i;
	char	**splits;

	i = 0;
	splits = malloc(sizeof(char *) * (*wcount + 1));
	if (!splits)
		return (NULL);
	while (i < (*wcount))
	{
		splits[i] = fill_arrays(s, c, first);
		if (!splits[i])
		{
			while ((i - 1) >= 0)
				free(splits[--i]);
			free(splits);
			return (NULL);
		}
		i++;
	}
	splits[*wcount] = NULL;
	return (splits);
}

char	**ft_split(char const *s, char c)
{
	char	**splits;
	int		wcount;
	int		first;

	if (!s)
		return (NULL);
	first = 0;
	wcount = word_count(s, c);
	splits = splitter(s, c, &first, &wcount);
	return (splits);
}
