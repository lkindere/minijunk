/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:56:14 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 17:24:09 by lkindere         ###   ########.fr       */
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
	if (!flag.p_open && !flag.p_close)
		return (-1);
	if (flag.p_open != flag.p_close)
		return (1);
	return (0);
}

//Returns 0 if not a subshell
//Returns 1 if subshell
//Removes outter parenthesis and returns
int	is_subshell(char **segment)
{
	int	valid;

	valid = is_valid(*segment);
	if (valid == -1)
		return (0);
	ft_find_replace(*segment, '(', ' ', 1);
	ft_find_replace(*segment, ')', ' ', -1);
	return (1);
}
