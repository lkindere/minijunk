/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:27:23 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 21:54:10 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_flags(t_flags *flags)
{
	flags->single_quote = 0;
	flags->double_quote = 0;
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
		if (is_meta(expansion[i]) && expansion[i] != ' ')
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

char	*rewrite_input(char *input, char *expansion, int *i, int *dollar_len)
{
	char	*old_input;

	old_input = input;
	expansion = quote_meta(expansion);
	input = ft_strionjoin(input, expansion, *dollar_len, i);
	free(expansion);
	free(old_input);
	expansion = NULL;
	*dollar_len = 0;
	return (input);
}

//Iterates through the input checking for quotes and dollar signs
char	*expander(char *input, t_data *data)
{
	t_flags	flags;
	char	*expansion;
	int		dollar_len;
	int		i;

	i = -1;
	dollar_len = 0;
	init_flags(&flags);
	while (input && input[++i])
	{
		if (input[i] == '\'' && !flags.double_quote)
			flags.single_quote = ~flags.single_quote & 1;
		if (input[i] == '"' && !flags.single_quote)
			flags.double_quote = ~flags.double_quote & 1;
		while (input[i] == '$' && input[i + 1] && !flags.double_quote)
		{
			expansion = expand_var(&input[i + 1], data, &dollar_len);
			input = rewrite_input(input, expansion, &i, &dollar_len);
		}
	}
	if (flags.double_quote || flags.single_quote)
		printf("Syntax error: unclosed quotes\n");
	return (input);
}
