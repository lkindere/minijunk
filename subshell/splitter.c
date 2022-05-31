/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 07:22:00 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/31 17:09:03 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

//Opens pipes on data
//Frees segment and returns 1 on error
//Returns 0 on success
static int	handle_pipe(t_data *data, char **input, int i)
{
	// printf("Handling pipe i: %d\n", i);
	if (data->pipe1[0] == -1 && data->pipe1[1] == -1)
	{
		if (pipe(data->pipe1) != 0)
		{
			free(*input);
			(*input) = NULL;
			return (1);
		}
		remove_separator(input, i);
		return (0);
	}
	if (data->pipe2[0] == -1 && data->pipe2[1] == -1)
	{
		if (pipe(data->pipe2) != 0)
		{
			free(*input);
			(*input) = NULL;
			return (1);
		}
		remove_separator(input, i);
		return (0);
	}
	return (0);
}





//Returns first character encountered after spaces
static int	first_sep(const char *segment)
{
	int	i;

	i = 0;
	while (segment[i] && ft_isspace(segment[i]))
		i++;
	if (!is_separator(segment[i]))
		return ('N');
	return (segment[i]);
}

//Returns 1 on &&
//Returns 1 on ||
//Returns 1 on | or < preceeded by closed parenthesis
//Returns 1 on | or < succeeded by opening parenthesis
//Returns 0 if no split is needed
static int	should_split(char *input, t_flag flag, int i)
{
	// printf("Flags p open: %d, p close: %d\n", flag.p_open, flag.p_close);
	if (i == 0)
		return (0);
	// printf("Checking %s\n\n", &input[i]);
	// printf("Flag open: %d, close: %d\n", flag.p_open, flag.p_close);
	if (flag.p_open == flag.p_close)
	{
		if (input[i] == '&' && input[i + 1] == '&')
			return (1);
		if (input[i] == '|' && input[i + 1] == '|')
			return (1);
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (flag.p_open > 0 || first_sep(&input[i + 1]) == '(')
			{
			 	// printf("Should split: %s %d returning 1\n\n", &input[i], i);
				return (1);
			}
		}
	}
	if (input[i] == '|' || input[i] == '<' || input[i] == '>')
	{
		while (input[i] && !split_separator(input[i], flag))
		{
			// printf("Wat, checking, %s, index %d\n", &input[i], i);
			set_flag(input[i], &flag);
			if (input[i++] == '(' && !is_quoted(flag))
				return (1);
		}
	}
	// printf("Flags p open: %d, p close: %d\n", flag.p_open, flag.p_close);
	// printf("Should split: %s %d returning 0\n", &input[i], i);
	return (0);
}

//Iterates through input and checks for flags or separator
//Returns index if a split is needed
//Returns -1 if no split is needed
static int	get_index(t_data *data, char **input)
{
	int		i;
	t_flag	flag;

	i = -1;
	init_flag(&flag);
	while ((*input)[++i])
	{
		// printf("Input i: %c, %d  ", (*input)[i], i);
		set_flag((*input)[i], &flag);
		// printf("Split sep: %d\n", split_separator((*input)[i], flag));
		if (split_separator((*input)[i], flag) && should_split(*input, flag, i))
		{
			// printf("Split sep i: %d\n", i);
			if ((*input)[i] == '|' && (*input)[i + 1] != '|')
			{
				if (handle_pipe(data, input, i) == 1)
					return (-1);
			}
			return (i);
		}
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
int	splitter(t_data *data, char **input, char **segment)
{
	int	end;

	if (!(*input))
		return (0);
	end = get_index(data, input);
	// printf("End: %d\n", end);
	if (end != -1)
		return (split_input(input, segment, end));
	if (end == -1)
	{
		(*segment) = (*input);
		(*input) = NULL;
	}
	return (0);
}
