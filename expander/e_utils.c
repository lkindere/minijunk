/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:00:41 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/30 07:42:45 by lkindere         ###   ########.fr       */
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

//Retrieves variables from envp
char	*retrieve_var(char **envp, int index)
{
	int		i;
	char	*expanded_var;

	i = 0;
	while (envp[index][i] != '=')
		i++;
	if (envp[index][i] == '=')
		i++;
	expanded_var = ft_strdup(&envp[index][i]);
	if (!expanded_var)
		internal_error_return(ERROR_MALLOC);
	return (expanded_var);
}

//Sets all struct data to 0, i to -1
void	init_expander(t_expander *xp)
{
	xp->i = 0;
	xp->dollar_len = 0;
	xp->single_quote = 0;
	xp->double_quote = 0;
	xp->expansion = NULL;
}
