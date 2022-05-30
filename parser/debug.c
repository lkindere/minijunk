/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:52:17 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/30 11:16:07 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 *	prints all token types and content.
 */
void	debug_print_tokens(t_data *data)
{
	t_token	*temp;

	temp = data->tokens;
	while (temp)
	{
		printf("type: %i \tcontent: \"%s\"\n", temp->type, temp->content);
		temp = temp->next;
	}
}

/*
 *	Prints the cmd index, followed by its arg.
 *	Also prints the in and out file descriptors of the command at the end.
 */
void	debug_print_cmds(t_data *data)
{
	t_cmd	*temp;
	int		i;

	temp = data->cmds;
	i = -1;
	while (temp)
	{
		while (temp->cmd_arg && temp->cmd_arg[++i])
			printf("string %i: %s\n", i, temp->cmd_arg[i]);
		// printf("string %i: %s\n", i, temp->cmd_arg[i]);
		printf("in: %i out: %i\n", temp->in, temp->out);
		temp = temp->pipe_next;
	}
}

/*
 *	prints all expands flags of the 2d array
 */
void	debug_print_expands(t_data *data)
{
	char	**temp_exp;
	int		i;

	i = 0;
	temp_exp = data->expands;
	while (temp_exp[i])
	{
		printf("Expand index p: %p\n", temp_exp[i]);
		// printf("expands: index: %i:\t%s\n", i, temp_exp[i]);
		i++;
	}
	printf("Expands i: %d\n", i);
}
