/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:58:40 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/27 12:29:55 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
 *	'free()'s and sets to NULL all members of the 2D array and the array itself.
 */
//Returns 1
int	free_2d_char(char ***cmds)
{
	int	i;

	i = 0;
	while ((*cmds)[i])
	{
		free((*cmds)[i]);
		(*cmds)[i] = NULL;
		i++;
	}
	free(*cmds);
	*cmds = NULL;
	return (1);
}

/*
 *	'free()'s all members of the t_cmd *cmds linked list passed as address of it
 *	and their content and sets it to NULL.
 */
void	free_cmds(t_cmd **cmds)
{
	t_cmd	**temp;

	temp = cmds;
	while (*cmds)
	{
		if ((*cmds)->cmd_arg)
			free_2d_char(&(*cmds)->cmd_arg);
		if ((*cmds)->paths)
			free_2d_char(&(*cmds)->paths);
		(*cmds)->pipe_prev = NULL;
		free((*cmds));
		(*cmds) = (*cmds)->pipe_next;
	}
	free(*temp);
	*temp = NULL;
}

/*
 *	'free()'s all tokens and their content in the linked list of tokens passed
 *	as address of pointer to start.
 */
void	free_tokens(t_token **tokens)
{
	t_token	*temp;

	while (*tokens)
	{
		temp = (*tokens)->next;
		if ((*tokens)->content)
		{
			free((*tokens)->content);
			(*tokens)->content = NULL;
		}
		free(*tokens);
		*tokens = temp;
	}
}

