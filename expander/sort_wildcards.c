/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_wildcards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:06:00 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 11:01:07 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	print_wildcards(char **wildcards)
{
	int	i;

	i = -1;
	while (wildcards[++i])
		printf("%d: %s ", i, wildcards[i]);
}

char	**sort_wildcards(char **wildcards)
{
	int		i;
	char	*temp;

	i = 0;
	if (!wildcards)
		return NULL;
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
