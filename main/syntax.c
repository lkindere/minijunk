/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:21:48 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/30 20:15:09 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	raw_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '\'' && !data->flags.double_quote)
			data->flags.single_quote = 1 - data->flags.single_quote;
		else if (data->input[i] == '\"' && !data->flags.single_quote)
			data->flags.double_quote = 1 - data->flags.double_quote;
		if (ft_isdigit(data->input[i])
			&& !(data->flags.single_quote || data->flags.double_quote)
			&& (data->input[i + 1] == '>' || data->input[i + 1] == '<'))
		{
			return (blank_err(data, "Positional parameters not handled", NULL));
		}
		i++;
	}
	if (data->flags.single_quote || data->flags.double_quote)
	{
		return (blank_err(data, "Unclosed quotes", NULL));
	}
	return (0);
}

int	checker(t_data *data)
{
	remove_double_end(data);
	if (check_invalid_words_amp(data) != 0)
		return (1);
	if (comb_redirs(data) != 0)
		return (2);
	if (check_content_between_par(data) != 0)
		return (3);
	if (check_input_each_cmd(data) != 0)
		return (4);
	if (check_even_par_count(data) != 0)
		return (5);
	return (0);
}

int	syntax_check(t_data *data, char **full_input)
{
	data->input = *full_input;
	if (raw_check(data) != 0)
	{
		reset_data(data);
		data->input = NULL;
		*full_input = NULL;
		return (1);
	}
	if (lexer(data) != 0 || checker(data) != 0)
	{
		reset_data(data);
		data->input = NULL;
		*full_input = NULL;
		return (1);
	}
	data->input = NULL;
	reset_data(data);
	return (0);
}
