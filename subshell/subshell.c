/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:56:14 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/24 19:09:19 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"


//Checks parenthesis and quotes
//If not a subshell returns -1
//If syntax error returns 1
//If subshell returns 0
static int	is_valid(char *segment)
{
	int		i;
	t_flag	flag;

	i = -1;
	init_flag(&flag);
	if (!segment)
		return (-1);
	while (segment[++i])
		set_flag(segment[i], &flag);
	// printf("Subshell p_open: %d, p_close: %d\n", flag.p_open, flag.p_close);
	if (!flag.p_open && !flag.p_close)
		return (-1);
	if (flag.p_open != flag.p_close)
		return (0);
	return (1);
}

//Returns 0 if not a subshell
//Returns 1 if subshell
//Removes outter parenthesis and returns
int	is_subshell(char **segment)
{
	int	valid;

	// printf("Input: %s\n", *segment);
	// printf("Checking is_subshell\n");
	valid = is_valid(*segment);
	if (valid == -1)
	{
		printf("Not a subshell\n");
		return (0);
	}
	// if (valid == 0)
	// {
	// 	printf("Syntax error\n");
	// 	free((*segment));
	// 	(*segment) = NULL;
	// 	return (-1);
	// }
	// printf("Finding and replacing\n");
	ft_find_replace(*segment, '(', ' ', 1);
	ft_find_replace(*segment, ')', ' ', -1);
	return (1);
}
