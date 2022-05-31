/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:53:41 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/31 11:57:52 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

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

static void	check_exit(t_data *data, char **segment, int and_or)
{
	if (!data->is_fork || data->start_code == -1)
		return ;
	if (data->start_code == 0 && and_or == 1)
		return ;
	if (data->start_code != 0 && and_or == 2)
		return ;
	free(*segment);
	(*segment) = NULL;
	terminator(&data);
}

//Checks the remainder of segment for separators
//Removes || and && setting and_or next
//Returns 0 on success
//Returns 1 on error
int	handle_and_or(t_data *data, char **segment, int *and_or)
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
		*and_or = 1;
		check_exit(data, segment, *and_or);
		return (remove_separator(segment, i));
	}
	if ((*segment)[i] == '|' && (*segment)[i + 1] == '|')
	{
		*and_or = 2;
		check_exit(data, segment, *and_or);
		return (remove_separator(segment, i));
	}
	if (data->is_fork)
		data->start_code = -1;
	return (0);
}
