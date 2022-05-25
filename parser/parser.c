/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:18:45 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/25 19:14:37 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	copy_redir(t_token *token)
{
	free(token->content);
	token->content = ft_strdup(token->next->content);
	if (token->content == NULL)
		return (internal_error_return(ERROR_MALLOC));
	// printf("TEST: content inside copy_dir: %s\n", token->content);
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
			return (ft_syntax_err(temp->next->content));
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

/*
 *	Checks the token list to see if every command has at least one token before
 *	next command starts or input ends.
 *	If not, throws an error and returns with != 0.
 */
int	check_input_each_cmd(t_data *data)
{
	int	cmds;
	int	has_input;
	t_token	*temp;

	cmds = 0;
	has_input = 0;
	temp = data->tokens;
	while (temp)
	{
		if (temp->type == PIPE || temp->type == END)
		{
			if (has_input == 0)
				return (ft_syntax_err(temp->content));
			has_input = 0;
		}
		else if (temp->type != PIPE)
			has_input = 1;
		temp = temp->next;
	}
	return (0);
}

int	parser(t_data *data)
{
	if (comb_redirs(data) != 0)
		return (1);
	remove_double_end(data);
	if (check_input_each_cmd(data) != 0)
		return (2);
	if (create_cmd_args(data) != 0)
		return (3);
	save_redirs_in_cmds(data);
	return (0);
}
