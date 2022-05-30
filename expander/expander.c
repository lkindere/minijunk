/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:27:23 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/30 21:06:34 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	is_exp(int single_quote, char c)
{
	if (single_quote)
		return (0);
	if (ft_isalnum(c) || c == '_' || c == '_')
		return (1);
	if (c == '"' || c == '\'')
		return (2);
	if (c == '?')
		return (3);
	return (0);
}

//Checks for variables
char	*expand_var(char *input, t_data *data, int *dollar_len)
{
	char	*var;
	int		index;
	int		i;

	i = 0;
	if (input[i] == '?')
	{
		*dollar_len = 2;
		return (ft_itoa(exit_code(-1)));
	}
	while (input[i] && is_exp(0, input[i]) == 1)
		i++;
	*dollar_len = i + 1;
	var = ft_substr_append(input, 0, i, '=');
	if (!var)
		internal_error_return(ERROR_MALLOC);
	index = is_set(var, data->envp);
	free(var);
	if (index >= 0)
		return (retrieve_var(data->envp, index));
	return (NULL);
}

char	*rewrite_input(char *input, t_expander *xp)
{
	char	*old_input;
	char	*old_exp;

	if ((!xp->expansion) && xp->double_quote)
	{
		xp->i += 2;
		return (input);
	}
	old_input = input;
	old_exp = xp->expansion;
	xp->expansion = quote_meta(xp->expansion);
	free(old_exp);
	input = ft_strionjoin(input, xp->expansion, xp->dollar_len, &xp->i);
	if (!xp->expansion)
		xp->i--;
	free(xp->expansion);
	free(old_input);
	xp->expansion = NULL;
	xp->dollar_len = 0;
	return (input);
}

//Iterates through the input checking for quotes and dollar signs
//if not heredoc, expands based on quotes
//If heredoc = 1, expands everything
//if heredoc = 2, expands nothing
char	*expander(char *input, t_data *data, int heredoc)
{
	t_expander	xp;

	if (heredoc == 2)
		return (input);
	init_expander(&xp);
	while (input && input[xp.i])
	{
		if (!heredoc)
		{
			if (input[xp.i] == '\'' && !xp.double_quote)
				xp.single_quote = ~xp.single_quote & 1;
			if (input[xp.i] == '"' && !xp.single_quote)
				xp.double_quote = ~xp.double_quote & 1;
		}
		while (input[xp.i] == '$' && is_exp(xp.single_quote, input[xp.i + 1]))
		{
			xp.expansion = expand_var(&input[xp.i + 1], data, &xp.dollar_len);
			input = rewrite_input(input, &xp);
		}
		if (input[xp.i])
			xp.i++;
	}
	return (input);
}
