/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:53:41 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/01 21:08:34 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

// Returns first character encountered after spaces
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

void	cut_subshell(char **segment, int i)
{
	t_flags	flag;

	flag.single_quote = 0;
	flag.double_quote = 0;
	while ((*segment)[i])
	{
		if ((*segment)[i] == '\'')
			flag.single_quote = ~flag.single_quote & 1;
		if ((*segment)[i] == '"')
			flag.double_quote = ~flag.double_quote & 1;
		if ((*segment)[i] == ')' && !flag.double_quote && !flag.single_quote)
		{
			(*segment)[i] = ' ';
			break ;
		}
		(*segment)[i++] = ' ';
	}
}

void check_cut(char **segment, int and_or, int i)
{
	if (!(*segment)[i])
		return ;
	if (first_sep(&(*segment)[i]) == '(')
	{
		if (and_or == 1 && exit_code(-1) != 0)
			cut_subshell(segment, i);
		if (and_or == 2 && exit_code(-1) == 0)
			cut_subshell(segment, i);
	}
}

int	check_separators(char **segment, int *and_or, int i)
{
	// printf("\n\nCHECKING SEPARATORS\n\n");
	if ((*segment)[i] == '&' && (*segment)[i + 1] == '&')
	{	
		// printf("\nFound and\n");
		// printf("Last exit code: %d\n", exit_code(-1));
		*and_or = 1;
		check_cut(segment, *and_or, i + 2);
		return (remove_separator(segment, i));
	}
	if ((*segment)[i] == '|' && (*segment)[i + 1] == '|')
	{
		// printf("\nFound or\n");
		// printf("Last exit code: %d\n", exit_code(-1));
		*and_or = 2;
		check_cut(segment, *and_or, i + 2);
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

	if (data)
		;
	i = 0;
	flag.single_quote = 0;
	flag.double_quote = 0;
	if (!(*segment))
		return (0);
	// printf("Segment before and_or: %s\n", *segment);
	while ((*segment)[i])
	{
		if (is_separator((*segment)[i]) && !flag.single_quote && !flag.double_quote)
			return (check_separators(segment, and_or, i));
		if ((*segment)[i] == '\'')
			flag.single_quote = ~flag.single_quote & 1;
		if ((*segment)[i] == '"')
			flag.double_quote = ~flag.double_quote & 1;
		i++;
	}
	// printf("Segment after and_or: %s\n", *segment);
	if (!(*segment)[i])
		return (0);
	return (0);
}
