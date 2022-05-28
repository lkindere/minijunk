/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 23:36:15 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/28 12:02:37 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//Resets back all (char)-1 to *
void	unhide_wildcards(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (cmd->cmd_arg[++i])
	{
		while (cmd->cmd_arg[i][++j])
		{
			if (cmd->cmd_arg[i][j] == (char)-1)
				cmd->cmd_arg[i][j] = '*';
		}
		j = -1;
	}
}

//Sets all expandable * to (char)-1
void	hide_wildcards(t_cmd *cmd)
{
	int	i;
	int	j;
	int	e;

	i = -1;
	j = -1;
	e = -1;
	while (cmd->cmd_arg[++i])
	{
		while (cmd->cmd_arg[i][++j])
		{
			if (cmd->cmd_arg[i][j] == '*' && cmd->exp[++e] == '1')
				cmd->cmd_arg[i][j] = (char)-1;
		}
		j = -1;
	}
}

//Sorts wildcards by ascii order
//Different versions of bash seem to either sort or not sort
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
