/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 09:57:51 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/23 16:40:17 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

typedef struct	s_par
{
	int	open;
	int close;
} t_par;

void	init_par(t_par *par)
{
	par->open = 0;
	par->close = 0;
}

int	is_subshell(int open, int close)
{
	if (open > 0 && open == close)
		return (1);
	return (0);
}

//Returns -1 on syntax error

int	not_subshell(t_par par, int c)
{
	if (par.close && !par.open)
		return (-1);
	if (c != ' ' && c != '(' && c != ')' && !par.open)
		return (1);
	return (0);
}

//Returns 1 on error
int	new_full_input(char **full_input, char **sub_input, int index)
{
	char	*old_full;
	int		i;

	i = 0;
	(*sub_input) = ft_substr(*full_input, 0, index);
	if (!(*sub_input))
		return (1);
	old_full = (*full_input);
	(*full_input) = ft_substr(*full_input, index, SIZE_MAX);
	free(old_full);
	if (!(*full_input))
		return (1);
	while ((*sub_input)[i] != '(')
		i++;
	while ((*sub_input)[index] != ')')
		index--;
	(*sub_input)[i] = ' ';
	(*sub_input)[index] = ' ';
	return (0);
}

//Iterate until open > 1 && open == close
//Returns -1 when no subshell
//Returns 1 when malloc error
//Returns 2 on syntax error
int	get_sub_input(t_par par, char **full_input, char **sub_input)
{
	int	i;

	i = -1;
	while ((*full_input)[++i] && !is_subshell(par.open, par.close))
	{
		if ((*full_input)[i] == '(')
			par.open++;
		if ((*full_input)[i] == ')')
			par.close++;
		if (not_subshell(par, (*full_input)[i]) == -1)
			return (2);
		if (not_subshell(par, (*full_input)[i]) == 1)
			return (-1);
	}
	if (!is_subshell(par.open, par.close))
		return (-1);
	if (par.open != par.close)
		return (2);
	if (new_full_input(full_input, sub_input, i) != 0)
		return (1);
	return (0);
}

//Returns 0 when not subshell
//Returns -1 on errors
//Returns 1 when subshell
int	subshells(char **full_input, char **sub_input)
{
	int		ret;
	t_par 	par;

	init_par(&par);
	ret = get_sub_input(par, full_input, sub_input);
	if (ret == -1)
		return (0);
	if (ret == 1)
	{
		printf("Malloc error\n");
		return (-1);
	}
	if (ret == 2)
	{
		printf("Syntax error\n");
		return (-1);
	}
	return (1);
}
