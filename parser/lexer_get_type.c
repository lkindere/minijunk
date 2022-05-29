/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:53:17 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/29 17:38:23 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_type	single_type(t_data *data, int *i)
{
	if (data->input[*i] == '|')
		return (PIPE);
	else if (data->input[*i] == '<')
		return (IN);
	else if (data->input[*i] == '>')
		return (OUT);
	else if (data->input[*i] == '\0')
		return (END);
	else if (data->input[*i] == '(')
		return (PAR_OPEN);
	else if (data->input[*i] == ')')
		return (PAR_CLOSE);
	else if (data->input[*i] == '&')
		return (AMPERSAND);
	else
		return (WORD);
}

/*
 *	Skips leading whitespaces and returns type of token.
 *	If it's a two character long token identifier (heredoc or append),
 *	moves i one spot (otherwise it would identify >> to be >> and > tokens).
 */
t_type	get_type(t_data *data, int *i)
{
	while (ft_isspace(data->input[*i]))
		(*i)++;
	if ((data->input[*i] == '<' && data->input[*i + 1] == '<')
			|| (data->input[*i] == '>' && data->input[*i + 1] == '>')
			|| (data->input[*i] == '&' && data->input[*i + 1] == '&')
			|| (data->input[*i] == '|' && data->input[*i + 1] == '|'))
	{
		(*i)++;
		if (data->input[*i - 1] == '<' && data->input[*i] == '<')
			return (HEREDOC);
		else if (data->input[*i - 1] == '>' && data->input[*i] == '>')
			return (APPEND);
		else if (data->input[*i - 1] == '&' && data->input[*i] == '&')
			return (LOG_AND);
		else
			return (LOG_OR);
	}
	return (single_type(data, i));
}
