/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:00:23 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/26 23:47:55 by lkindere         ###   ########.fr       */
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
 *	Checks the token list to see if every command has at least one token before
 *	next command starts or input ends.
 *	If not, throws an error and returns with != 0.
 */
int	check_input_each_cmd(t_data *data)
{
	int		has_input;
	t_token	*temp;

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

int	check_even_par_count(t_data *data)
{
	int		par_count;
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
		if (curr->type == PIPE && (next->type == PAR_CLOSE
			|| next->type == LOG_AND || next->type == LOG_OR))
			return (blank_err(data, "syntax", next->content));
		curr = curr->next;
	}
	return (0);
}
