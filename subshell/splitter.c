/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 07:22:00 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/01 20:44:25 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

//Returns 1 on &&
//Returns 1 on ||
//Returns 1 on | or < preceeded by closed parenthesis
//Returns 1 on | or < succeeded by opening parenthesis
//Returns 0 if no split is needed
static int	should_split(char *input, t_flag flag, int i)
{
	if (i == 0)
		return (0);
	if (flag.p_open == flag.p_close)
	{
		if (input[i] == '&' && input[i + 1] == '&')
			return (1);
		if (input[i] == '|' && input[i + 1] == '|')
			return (1);
	}
	return (0);
}

//Iterates through input and checks for flags or separator
//Returns index if a split is needed
//Returns -1 if no split is needed
static int	get_index(char **input)
{
	int		i;
	t_flag	flag;

	i = -1;
	init_flag(&flag);
	while ((*input)[++i])
	{
		set_flag((*input)[i], &flag);
		if (split_separator((*input)[i], flag) && should_split(*input, flag, i))
			return (i);
	}
	return (-1);
}

//Splits the input into segments
//Returns 1 on errors
//Returns 0 on success
static int	split_input(char **input, char **segment, int end)
{
	char	*old_input;

	old_input = (*input);
	(*segment) = ft_substr((*input), 0, end);
	if (!(*segment))
		return (1);
	(*input) = ft_substr((*input), end, SIZE_MAX);
	free(old_input);
	if (!(*input))
		return (1);
	return (0);
}

//Splits the input into segments
//Returns 1 on errors
//Returns 0 on success
int	splitter(char **input, char **segment)
{
	int	end;

	if (!(*input))
		return (0);
	end = get_index(input);
	if (end != -1)
		return (split_input(input, segment, end));
	if (end == -1)
	{
		(*segment) = (*input);
		(*input) = NULL;
	}
	return (0);
}
