/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:03:47 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 13:19:25 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static typedef struct s_split
{
	char	*s;
	char	c;
	int		n;
}	t_split;

static int	word_count(t_split *split)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (split->s[i] && i < split->n)
	{
		while (split->s[i] == split->c && split->s[i] && i < split->n)
			i++;
		if (split->s[i] != split->c && split->s[i] && i < split->n)
		{
			count++;
			while (split->s[i] != split->c && split->s[i] && i < split->n)
				i++;
		}
	}
	return (count);
}

static char	*fill_arrays(t_split *split, int *first)
{
	char	*str;
	int		i;
	int		last;

	i = 0;
	while (split->s[*first] == split->c && split->s[*first]
		&& *first < split->n)
		(*first)++;
	last = *first;
	while (split->s[last] != split->c && split->s[last] && last < split->n)
		(last)++;
	str = malloc((last - *first) + 1);
	if (!str)
		return (NULL);
	while (*first < last && *first < split->n)
	{
		str[i] = split->s[*first];
		(*first)++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**splitter(t_split *split, int *first, int *wcount)
{
	int		i;
	char	**splits;

	i = 0;
	splits = malloc(sizeof(char *) * (*wcount + 1));
	if (!splits)
		return (NULL);
	while (i < (*wcount))
	{
		splits[i] = fill_arrays(split, first);
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

//Splits up to n characters from the string
char	**ft_splitn(char const *s, char c, int n)
{
	t_split	split;
	char	**splits;
	int		wcount;
	int		first;
	int		i;

	if (!s)
		return (NULL);
	split.s = (char *) s;
	split.c = c;
	split.n = n;
	i = 0;
	first = 0;
	wcount = word_count(&split);
	splits = splitter(&split, &first, &wcount);
	return (splits);
}
