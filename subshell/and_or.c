/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:53:41 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/31 17:14:50 by lkindere         ###   ########.fr       */
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

int	check_separators(t_data *data, char **segment, int *and_or, int i)
{
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
	return (0);
}

//Checks the remainder of segment for separators
//Removes || and && setting and_or next
//Returns 0 on success
//Returns 1 on error
int	handle_and_or(t_data *data, char **segment, int *and_or)
{
	t_flags	flag;
	int		i;

	i = 0;
	flag.single_quote = 0;
	flag.double_quote = 0;
	if (!(*segment))
		return (0);
	while ((*segment)[i])
	{
		if (is_separator((*segment)[i]) && !flag.single_quote && !flag.double_quote)
			return (check_separators(data, segment, and_or, i));
		if ((*segment)[i] == '\'')
			flag.single_quote = ~flag.single_quote & 1;
		if ((*segment)[i] == '"')
			flag.double_quote = ~flag.double_quote & 1;
		i++;
	}
	if (!(*segment)[i])
		return (0);
	if (data->is_fork)
		data->start_code = -1;
	return (0);
}
