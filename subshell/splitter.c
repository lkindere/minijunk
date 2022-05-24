/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 07:22:00 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/24 09:48:54 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "exec.h"

typedef struct s_flag
{
	int p_open;
	int p_close;
	int s_quote;
	int d_quote;
} t_flag;

//Inits flags to 0
static void    init_flags(t_flag *flag)
{
	flag->p_open = 0;
	flag->p_close = 0;
	flag->s_quote = 0;
	flag->d_quote = 0;
}

//Checks if quoted
static int is_quoted(t_flag flag)
{
	if (flag.s_quote == 1)
		return (1);
	if (flag.d_quote == 1)
		return (1);
	return (0);
	}

//Increments parenthesis when encountered
//If not quoted sets quote to 1
//If quoted, resets quote to 0
static void	set_flag(int c, t_flag *flag)
{
	if (c == '(')
		flag->p_open++;
	else if (c == ')')
		flag->p_close++;
    if (!is_quoted(*flag))
    {
		if (c == '\'')
			flag->s_quote = 1;
		else if (c == '"')
			flag->d_quote = 1;
		return ;
    }
	if (c == '\'')
		flag->s_quote = 0;
	else if (c == '"')
		flag->d_quote = 0;
}

//Checks if it's a separator
static int	is_separator(int c, t_flag flag)
{
	if (is_quoted(flag))
		return (0);
	if (c == '&' || c == '|' || c == '<')
		return (1);
	return (0);
}

//Returns 1 on &&
//Returns 1 on ||
//Returns 1 on | or < preceeded by closed parenthesis
//Returns 1 on | or < succeeded by opening parenthesis
static int	should_split(char *input, t_flag flag, int i)
{
	if (index == 0)
		return (0);
	if (input[i] == '&' && input[i + 1] == '&')
		return (1);
	if (input[i] == '|' && input[i + 1] == '|')
		return (1);
	if (input[i] == '|' || input[i] == '<')
	{
		printf("P open: %d, P close: %d\n", flag.p_open, flag.p_close);
		if (flag.p_open > 0 && flag.p_close == flag.p_open)
			return (1);
		while (input[i++] && !is_separator(input[i], flag))
		{
			set_flag(input[i], &flag);
			if (input[i] == '(' && !is_quoted(flag))
				return (1);
		}
	}
	return (0);
}

//Iterates through input and checks for flags or separator
//Returns index if a split is needed
//Returns -1 if no split is needed
static int	get_index(char **input)
{
	int     i;
	t_flag flag;

	i = -1;
	init_flags(&flag);
	while ((*input)[++i])
	{
		set_flag((*input)[i], &flag);
		if (is_separator((*input)[i], flag) && should_split(*input, flag, i))
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
	printf("New segment: %s\n", *segment);
	printf("New input  : %s\n", *input);
}

//Splits the input into segments
//Returns 1 on errors
//Returns 0 on success
int splitter(char **input, char **segment)
{
	int end;

	printf("Start input: %s\n", *input);
	end = get_index(input);
	// printf("End is: %d\n", end);
	if (end != -1)
		return (split_input(input, segment, end));
	if (end == -1)
	{
		(*segment) = (*input);
		(*input) = NULL;
	}
	printf("New segment: %s\n", *segment);
	printf("New input  : %s\n", *input);
	return (0);
}
