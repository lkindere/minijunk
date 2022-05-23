/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:00:50 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/23 16:36:21 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"

// code/minishell$ (export abc=potatoes && echo $abc) && echo $abc
// potatoes


// ➜  minishell git:(master) ✗ (rm test && cat test)
// cat: test: No such file or directory

// code/minishell$ (rm junk && cat jun*)
// cat: 'jun*': No such file or directory

//Run each segment up until &&/|| individually then expand and do wildcards again
//data->input = 1 segment

int	is_split(int c, int d)
{
    if (c == '&' && d == '&')
        return (1);
    if (c == '|' && d == '|')
        return (2);
	if (c == '(')
		return (3);
    if (c == '&' && d != '&')
        return (-1);
	if (c == ')')
		return (-2);
    return (0);
}

//Need to fix for pipes later
int	is_separator(int c)
{
	if (c == '&' || c == '|' || c == ' ')
		return (1);
	return (0);
}

//Splits the input to data->input and new input
//Frees old input
//Returns 1 on error, 0 on success
int	split_inputs(t_data **data, char **input, int index, int len)
{
	char	*old_input;

	old_input = (*input);
	(*data)->input = ft_substr((*input), 0, index);
	if (!(*data)->input)
		return (1);
	(*input) = ft_substr((*input), index + len, SIZE_MAX);
	free(old_input);
	if (!(*input))
		return (1);
	return (0);
}

//Differentiates between parenthesis and && ||
//Returns 1 on exception (shouldn't be possible)
//Returns 0 on success
int	handle_split(t_data **data, char **input, int index, int split)
{
	int	trim;
	int	i;

	i = -1;
	trim = 1;
	while (index - ++i >= 0)
	{
		if (!is_separator((*input)[i]))
			trim = 0;
	}
	if (trim)
	{
		(*data)->and_or[0] = split;
		while (i >= 0)
			(*input)[i--] = ' ';
		return (0); 
	}
	if (split == 1 || split == 2)
	{
		(*data)->and_or[1] = split;
		return (split_inputs(data, input, index, 2));
	}
	if (split == 3)
		return (split_inputs(data, input, index, 0));
	return (1);
}

//Iterates through the input looking for parenthesis or && ||
//Returns 1 on error
//Returns -1 if no split is required
int	split_to_data(t_data **data, char **input)
{
    int i;
	int	split;

	i = -1;
	split = 0;
	while (*input && (*input)[++i] && !split)
	{
		split = is_split((*input)[i], (*input)[i + 1]);
		if (split < 0)
		{
			printf("Syntax error placeholder\n");
			return (1);
		}
		if (split > 0)
			return (handle_split(data, input, i, split));
	}
	return (-1);
}

//Switches the and_or from next to current command
//If no split, sets data input to full input
void    split_input(char **full_input, t_data **data)
{
	(*data)->and_or[0] = (*data)->and_or[1];
	(*data)->and_or[1] = 0;
    split_to_data(data, full_input);
	if (!(*data)->input)
	{
		(*data)->input = *full_input;
		*full_input = NULL;
	}
}