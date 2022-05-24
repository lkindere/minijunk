/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:53:41 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/24 22:11:18 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

//Checks if it's a separator
static int	is_separator(int c)
{
	if (c == '&' || c == '|' || c == '<' || c == '>')
		return (1);
	if (c == '(')
		return (1);
	return (0);
}

//Replaces && || | wih spaces
static int	remove_separator(char **input, int i)
{
	if ((*input)[i] == '|' || (*input)[i] == '&')
		(*input)[i] = ' ';
	if ((*input)[i + 1] == '|' || (*input)[i + 1] == '&')
		(*input)[i + 1] = ' ';
	// printf("\nSep New input  : %s\n", *input);
	return (0);
}

//Opens a pipe on data
//Frees input and returns 1 on error
static int	handle_pipe(t_data *data, char **input, int i)
{
	if (pipe(data->pipe) != 0)
	{
		free(*input);
		(*input) = NULL;
		return (1);
	}
	return (remove_separator(input, i));
}

//Returns first character encountered after spaces
int	first_sep(const char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (!is_separator(input[i]))
		return ('N');
	return (input[i]);
}

//Checks the remainder of input for separators
//Removes || and && setting and_or next
//Creates pipe if needed and removes |
//Returns 0 on success
//Returns 1 on error
int	handle_separators(t_data *data, char **input, int *and_or_next)
{
	int	i;

	i = 0;
	// printf("\nSep input  : %s\n", *input);
	if (!(*input))
		return (0);
	if (first_sep(*input) == '(' || first_sep(*input) == 'N')
		return (0);
	while ((*input)[i] && !is_separator((*input)[i]))
		i++;
	if (!(*input)[i])
		return (0);
	if ((*input)[i] == '|' && (*input)[i + 1] != '|')
		return (handle_pipe(data, input, i));
	if (first_sep(&((*input)[i + 2])) == '(')
		return (0);
	if ((*input)[i] == '&' && (*input)[i + 1] == '&')
	{	
		*and_or_next = 1;
		return (remove_separator(input, i));
	}
	if ((*input)[i] == '|' && (*input)[i + 1] == '|')
	{
		*and_or_next = 2;
		return (remove_separator(input, i));
	}
	return (0);
}
