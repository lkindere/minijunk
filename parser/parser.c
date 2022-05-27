/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:18:45 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/27 16:41:42 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	copy_redir(t_token *token)
{
	free(token->content);
	token->content = ft_strdup(token->next->content);
	if (token->content == NULL)
		return (internal_error_return(ERROR_MALLOC));
	return (0);
}

/*
 *	Groups any redirection type tokens with the next WORD token into one.
 *	If there is no WORD after a redirection type token, throws an error.
 */
int	comb_redirs(t_data *data)
{
	t_token	*temp;

	temp = data->tokens;
	while (temp)
	{
		if (is_redir(temp->type) && temp->next && temp->next->type != WORD)
			return (blank_err(data, "syntax", temp->next->content));
		else if (is_redir(temp->type) && temp->next && temp->next->type == WORD)
		{
			if (copy_redir(temp) != 0)
				return (1);
			del_next_token(temp);
		}
		temp = temp->next;
	}
	return (0);
}

/*
 *	If there are two END tokens (happens when there are spaces at end of input),
 *	removes the second one.
 */
void	remove_double_end(t_data *data)
{
	t_token	*temp;

	temp = data->tokens;
	while (temp)
	{
		if (temp->type == END && temp->next && temp->next->type == END)
			del_token(&(temp->next));
		temp = temp->next;
	}
}

int	parser(t_data *data)
{
	// if (checker(data) != 0)
	// 	return (1);
	if (comb_redirs(data) != 0)
		return (2);
	// printf("survived even_par_count\n");
	if (create_cmd_args(data) != 0)
		return (6);
	// printf("survived create_cmd_args\n");
	save_redirs_in_cmds(data);
	remove_double_end(data);
	// debug_print_cmds(data);
	return (0);
}
