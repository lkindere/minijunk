/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:21:48 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/26 21:36:13 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	raw_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '\'' && data->flags.single_quote)
			data->flags.single_quote = 1 - data->flags.single_quote;
		else if (data->input[i] == '\"' && data->flags.double_quote)
			data->flags.double_quote = 1 - data->flags.double_quote;
		if (ft_isdigit(data->input[i])
			&& !(data->flags.single_quote || data->flags.double_quote)
			&& (data->input[i + 1] == '>' || data->input[i + 1] == '<'))
		{
			blank_err(data, "Positional parameters not handled, syntax", NULL);
			return (1);
		}
		i++;
	}
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
	if (lexer(data) != 0 || parser(data) != 0)
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
