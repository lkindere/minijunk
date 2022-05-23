/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:27:23 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/22 20:23:26 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"

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
		printf("Malloc fail\n");
	return (expanded_var);
}


//Checks for variables
char	*expand_var(char *input, t_data *data, int *dollar_len)
{
	char	*var;
	int		index;
	int		i;

	i = 0;
	// if (input[i] + 1 == '?' || input[i + 1] == DIGIT)
	//Edge cases, in case of digit cuts off first digit, prints out the rest
	while (input[i] && !is_meta(input[i]))
		i++;
	if (i > 0)
	{
		*dollar_len = i + 1;
		var = ft_substr_append(input, 0, i, '=');
		if (!var)
			return (NULL);
		index = is_set(var, data->envp);
		free(var);
		if (index >= 0)
		{
			var = retrieve_var(data->envp, index);
			return (var);
		}
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
	// printf("Allocated for: %d\n", i + (meta * 2) + 1);
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
	// printf("Quoted: %s\n", quoted);
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

	i = 0;
	dollar_len = 0;
	init_flags(&flags);
	while (input && input[i])
	{
		if (input[i] == '\'' && !flags.double_quote)
			flags.single_quote = ~flags.single_quote & 1;
		if (input[i] == '"' && !flags.single_quote)
			flags.double_quote = ~flags.double_quote & 1;
		if (input[i] == '$' && input[i + 1] && !flags.double_quote)
		{
			expansion = expand_var(&input[i + 1], data, &dollar_len);
			input = rewrite_input(input, expansion, &i, &dollar_len);
		}
		i++;
	}
	if (flags.double_quote || flags.single_quote)
		printf("Syntax error: unclosed quotes\n");
	return (input);
}
