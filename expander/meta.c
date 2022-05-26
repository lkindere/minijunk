/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:21:06 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 19:08:46 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//Allocates extra for every quote of meta characters
static char	*alloc_meta(char *expansion)
{
	char	*alloc;
	int		i;
	int		meta;

	i = 0;
	meta = 0;
	if (!expansion || !expansion[i])
		return (NULL);
	while (expansion && expansion[i])
	{
		if (is_meta(expansion[i]))
			meta++;
		i++;
	}
	alloc = malloc(i + (meta * 2) + 1);
	if (!alloc)
		internal_error_return(ERROR_MALLOC);
	return (alloc);
}

//Quotes every meta character with single quotes and returns the string
char	*quote_meta(char *expansion)
{
	char	*quoted;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quoted = alloc_meta(expansion);
	if (!quoted)
		return (NULL);
	while (expansion && expansion[i])
	{
		if (is_meta(expansion[i]) && !ft_isspace(expansion[i]))
		{
			quoted[j++] = '\'';
			quoted[j++] = expansion[i++];
			quoted[j++] = '\'';
		}
		else
			quoted[j++] = expansion[i++];
	}
	quoted[j] = 0;
	return (quoted);
}
