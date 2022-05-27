/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:27:23 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/27 15:36:29 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	is_exp(int single_quote, char c)
{
	if (single_quote)
		return (0);
	return (ft_isalnum(c) || c == '_' || c == '?');
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
		return (ft_itoa(data->exit_code));
	}
	while (input[i] && is_exp(0, input[i]))
		i++;
	if (i > 0)
	{
		*dollar_len = i + 1;
		var = ft_substr_append(input, 0, i, '=');
		if (!var)
			internal_error_return(ERROR_MALLOC);
		index = is_set(var, data->envp);
		free(var);
		if (index >= 0)
			return (retrieve_var(data->envp, index));
	}
	return (NULL);
}

char	*rewrite_input(char *input, t_expander *xp)
{
	char	*old_input;

	old_input = input;
	xp->expansion = quote_meta(xp->expansion);
	input = ft_strionjoin(input, xp->expansion, xp->dollar_len, &xp->i);
	free(xp->expansion);
	free(old_input);
	xp->expansion = NULL;
	xp->dollar_len = 0;
	return (input);
}

//Iterates through the input checking for quotes and dollar signs
char	*expander(char *input, t_data *data)
{
	t_expander	xp;

	init_expander(&xp);
	while (input && input[++xp.i])
	{
		if (input[xp.i] == '\'' && !xp.double_quote)
			xp.single_quote = ~xp.single_quote & 1;
		if (input[xp.i] == '"' && !xp.single_quote)
			xp.double_quote = ~xp.double_quote & 1;
		while (input[xp.i] == '$' && is_exp(xp.single_quote, input[xp.i]))
		{
			xp.expansion = expand_var(&input[xp.i + 1], data, &xp.dollar_len);
			input = rewrite_input(input, &xp);
		}
	}
	return (input);
}
