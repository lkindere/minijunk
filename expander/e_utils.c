/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:00:41 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 19:09:23 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	**sort_wildcards(char **wildcards)
{
	int		i;
	char	*temp;

	i = 0;
	if (!wildcards)
		return (NULL);
	while (wildcards[i] && wildcards[i + 1])
	{
		if (ft_strcmp(wildcards[i], wildcards[i + 1]) > 0)
		{	
			temp = wildcards[i];
			wildcards[i] = wildcards[i + 1];
			wildcards[i + 1] = temp;
			i = -1;
		}
		i++;
	}
	return (wildcards);
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
	xp->i = -1;
	xp->dollar_len = 0;
	xp->single_quote = 0;
	xp->double_quote = 0;
	xp->expansion = NULL;
}
