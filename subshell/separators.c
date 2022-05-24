/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:53:41 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/24 09:54:16 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

//Checks if it's a separator
static int	is_separator(int c)
{
	if (c == '&' || c == '|' || c == '<')
		return (1);
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
 
//Replaces && || | wih spaces
static int	remove_separator(char **input, int i)
{
	if ((*input)[i] == '|' || (*input)[i] == '&')
		(*input)[i] = ' ';
	if ((*input)[i + 1] == '|' || (*input)[i + 1] == '&')
		(*input)[i + 1] = ' ';
	printf("Removed sep: %s\n", (*input));
	return (0);
}

//Checks the remainder of input for separators
//Removes || and &&
//Creates pipe if needed and removes |
//Returns 0 on success
//Returns 1 on error
int	handle_separators(t_data *data, char **input)
{
	int	i;

	i = 0;
	if (!(*input))
		return ;
	while ((*input)[i] && !is_separator((*input)[i]))
		i++;
	if (!(*input)[i])
		return ;
	if ((*input)[i] == '&' && (*input)[i + 1] == '&'
		|| (*input)[i] == '|' && (*input)[i + 1] == '|')
		return (remove_separator(input, i));
	if ((*input)[i] == '|' && (*input)[i + 1] != '|')
		return (handle_pipe(data, input, i));
}
