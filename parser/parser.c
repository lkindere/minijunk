/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:18:45 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/26 13:44:33 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_invalid_words_amp(t_data *data)
{
	t_token	*temp;

	temp = data->tokens;
	while (temp)
	{
		if (temp->type == AMPERSAND)
			return (blank_err(data, "Unhandled", "&"));
		temp = temp->next;
	}
	return (0);
}

/*
 *	Throws an error in case parentheses are used wrongly.
 *	This includes not allowing "&&", "||" and ")" directly after 
 *	"(", "&&" and "||".
 *	Also, after ")", there must be either another ")", "&&", "||" or
 *	end of input.
 */
int	check_content_between_par(t_data *data)
{
	t_token	*curr;
	t_token	*next;

	curr = data->tokens;
	while (curr)
	{
		next = curr->next;
		if ((curr->type == PAR_OPEN || curr->type == LOG_AND
			|| curr->type == LOG_OR) && (next->type == LOG_AND
			|| next->type == LOG_OR || next->type == PAR_CLOSE
			|| next->type == PIPE))
			return (blank_err(data, "syntax", next->content));
		if (curr->type == PAR_CLOSE && (next->type != PAR_CLOSE
			&& next->type != LOG_AND && next->type != LOG_OR
			&& next->type != END && next->type != PIPE))
			return (blank_err(data, "syntax", next->content));
		curr = curr->next;
	}
	return (0);
}

int	check_even_par_count(t_data *data)
{
	int	par_count;
	t_token	*temp;

	par_count = 0;
	temp = data->tokens;
	while (temp)
	{
		if (par_count < 0)
			return (blank_err(data, "unopened parenthesis closed syntax", NULL));
		if (temp->type == PAR_OPEN)
			par_count++;
		else if (temp->type == PAR_CLOSE)
			par_count--;
		temp = temp->next;
	}
	if (par_count == 0)
		return (0);
	else
		return (blank_err(data, "unclosed parenthesis syntax", NULL));
}

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
				return (blank_err(data, "syntax", temp->content));
			has_input = 0;
		}
		else if (temp->type != PIPE && temp->type != LOG_AND
				&& temp->type != LOG_OR && temp->type != PAR_OPEN
				&& temp->type != PAR_CLOSE)
			has_input = 1;
		temp = temp->next;
	}
	return (0);
}

int	parser(t_data *data)
{
	if (check_invalid_words_amp(data) != 0)
		return (1);
	if (comb_redirs(data) != 0)
		return (2);
	remove_double_end(data);
	if (check_input_each_cmd(data) != 0)
		return (3);
	if (check_even_par_count(data) != 0)
		return (4);
	if (check_content_between_par(data) != 0)
		return (5);
	if (create_cmd_args(data) != 0)
		return (6);
	save_redirs_in_cmds(data);
	return (0);
}
