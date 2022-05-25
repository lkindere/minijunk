/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:53:41 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 11:50:09 by lkindere         ###   ########.fr       */
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

//Returns first character encountered after spaces
int	first_sep(const char *segment)
{
	int	i;

	i = 0;
	while (segment[i] && segment[i] == ' ')
		i++;
	if (!is_separator(segment[i]))
		return ('N');
	return (segment[i]);
}

//Checks the remainder of segment for separators
//Removes || and && setting and_or next
//Returns 0 on success
//Returns 1 on error
int	handle_separators(t_data *data, char **segment, int *and_or_next)
{
	int	i;

	i = 0;
	if (!(*segment))
		return (0);
	while ((*segment)[i] && !is_separator((*segment)[i]))
		i++;
	if (!(*segment)[i])
		return (0);
	if (first_sep(&((*segment)[i + 2])) == '(')
		return (0);
	if ((*segment)[i] == '&' && (*segment)[i + 1] == '&')
	{	
		*and_or_next = 1;
		return (remove_separator(segment, i));
	}
	if ((*segment)[i] == '|' && (*segment)[i + 1] == '|')
	{
		*and_or_next = 2;
		return (remove_separator(segment, i));
	}
	return (0);
}
