/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:27:23 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 17:58:31 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

typedef	struct s_expander
{
	int		i;
	int		dollar_len;
	int		single_quote;
	int		double_quote;
	char	*expansion;
} t_expander;

void	init_expander(t_expander *xp)
{
	xp->i = -1;
	xp->dollar_len = 0;
	xp->single_quote = 0;
	xp->double_quote = 0;
	xp->expansion = NULL;
}

//Retrieves variables from envp
char	*retrieve_var(char **envp, int index)
{
	int		i;
	char	*expanded_var;

	i = 0;
	while (envp[index][i] != '=')
		i++;
	if (envp[index][i] == '=')
		i++;
	expanded_var = ft_strdup(&envp[index][i]);
	if (!expanded_var)
		internal_error_return(ERROR_MALLOC);
	return (expanded_var);
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
	while (input[i] && input[i] != '$' && !is_meta(input[i]))
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

char	*alloc_meta(char *expansion)
{
	char	*alloc;
	int		i;
	int		meta;

	i = 0;
	meta = 0;
	if (!expansion || !expansion[i])
		return (NULL);
	while (expansion && expansion[i])
	{
		if (is_meta(expansion[i]))
			meta++;
		i++;
	}
	alloc = malloc(i + (meta * 2) + 1);
	if (!alloc)
		internal_error_return(ERROR_MALLOC);
	return (alloc);
}

char	*quote_meta(char *expansion)
{
	char	*quoted;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quoted = alloc_meta(expansion);
	if (!quoted)
		return (NULL);
	while (expansion && expansion[i])
	{
		if (is_meta(expansion[i]) && !ft_isspace(expansion[i]))
		{
			quoted[j++] = '\'';
			quoted[j++] = expansion[i++];
			quoted[j++] = '\'';
		}
		else 
			quoted[j++] = expansion[i++];
	}
	quoted[j] = 0;
	return (quoted);
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
	
	printf("Input: %s\n", input);
	init_expander(&xp);
	while (input && input[++xp.i])
	{
		if (input[xp.i] == '\'' && !xp.double_quote)
			xp.single_quote = ~xp.single_quote & 1;
		if (input[xp.i] == '"' && !xp.single_quote)
			xp.double_quote = ~xp.double_quote & 1;
		while (input[xp.i] == '$' && input[xp.i + 1] && !xp.single_quote)
		{
			printf("Expanding\n");
			xp.expansion = expand_var(&input[xp.i + 1], data, &xp.dollar_len);
			printf("Expansion: %s\n", xp.expansion);
			input = rewrite_input(input, &xp);
		}
	}
	printf("Expander: %s\n", input);
	return (input);
}
