/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 07:22:00 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 13:08:00 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

//Opens a pipe on data
//Frees segment and returns 1 on error
static int	handle_pipe(t_data *data, char **input, int i)
{
	if (data->pipe1[0] == -1 && data->pipe1[1] == -1)		//If pipe 1 is not in use pipe to pipe1
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
	if (data->pipe2[0] == -1 && data->pipe2[1] == -1)		//If pipe 2 is not in use pipe to pipe2
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
	printf("Creating pipes not working as expected\n");
	return (0);
}

//Checks if it's a separator
static int	is_separator(int c, t_flag flag)
{
	if (is_quoted(flag))
		return (0);
	if (c == '&' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

//Returns 1 on &&
//Returns 1 on ||
//Returns 1 on | or < preceeded by closed parenthesis
//Returns 1 on | or < succeeded by opening parenthesis
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
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (flag.p_open > 0)
				return (1);
		}
	}
	if (input[i] == '|' || input[i] == '<' || input[i] == '>')
	{
		while (input[i] && !is_separator(input[i], flag))
		{
			set_flag(input[i], &flag);
			if (input[i++] == '(' && !is_quoted(flag))
				return (1);
		}
	}
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
		set_flag((*input)[i], &flag);
		if (is_separator((*input)[i], flag) && should_split(*input, flag, i))
		{
			if ((*input)[i] == '|' && (*input)[i + 1] != '|')
        		if (handle_pipe(data, input, i) == 1)
					return (-1);
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
	// printf("New segment: %s\n", *segment);
	// printf("New input  : %s\n", *input);
	return (0);
}

//Splits the input into segments
//Returns 1 on errors
//Returns 0 on success
int splitter(t_data *data, char **input, char **segment)
{
	int end;

	if (!(*input))
		return (0);
	// printf("\nSplit Start input: %s\n", *input);
	// printf("Start input: %s\n", *input);
	end = get_index(data, input);
	// printf("End is: %d\n", end);
	if (end != -1)
		return (split_input(input, segment, end));
	if (end == -1)
	{
		(*segment) = (*input);
		(*input) = NULL;
	}
	// printf("\nSplit New segment: %s\n", *segment);
	// printf("\nSplit New input  : %s\n\n", *input);

	return (0);
}
