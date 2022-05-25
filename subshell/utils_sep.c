/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:50:31 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 17:54:56 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

//Checks if it's a separator (separators version)
int	is_separator(int c)
{
	if (c == '&' || c == '|' || c == '<' || c == '>')
		return (1);
	if (c == '(')
		return (1);
	return (0);
}

//Checks if it's a separator (splitter version)
int	splitter_separator(int c, t_flag flag)
{
	if (is_quoted(flag))
		return (0);
	if (c == '&' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

//Replaces && || | wih spaces
int	remove_separator(char **segment, int i)
{
	if ((*segment)[i] == '|' || (*segment)[i] == '&')
		(*segment)[i] = ' ';
	if ((*segment)[i + 1] == '|' || (*segment)[i + 1] == '&')
		(*segment)[i + 1] = ' ';
	// printf("\nSep New segment  : %s\n", *segment);
	return (0);
}
