/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:58:15 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 19:30:58 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

//Checks if the input has a valid start
int	is_start(const char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (input[i] == '(' || input[i] == ')' || input[i] == '&')
		return (0);
	if (input[i] == '|' && input[i + 1] == '|')
		return (0);
	return (1);
}

//Inits flags to 0
void	init_flag(t_flag *flag)
{
	flag->p_open = 0;
	flag->p_close = 0;
	flag->s_quote = 0;
	flag->d_quote = 0;
}

//Checks if quoted
int	is_quoted(t_flag flag)
{
	if (flag.s_quote == 1)
		return (1);
	if (flag.d_quote == 1)
		return (1);
	return (0);
}

//Increments parenthesis when encountered
//If not quoted sets quote to 1
//If quoted, resets quote to 0
void	set_flag(int c, t_flag *flag)
{
	if (!is_quoted(*flag))
	{
		if (c == '(')
			flag->p_open++;
		else if (c == ')')
			flag->p_close++;
		else if (c == '\'')
			flag->s_quote = 1;
		else if (c == '"')
			flag->d_quote = 1;
		return ;
	}
	if (c == '\'')
		flag->s_quote = 0;
	else if (c == '"')
		flag->d_quote = 0;
}

//Checks and_or and exit code
int	can_execute(int and_or, int exit_code)
{
	if (and_or == 0)
		return (1);
	if (and_or == 1 && exit_code == 0)
		return (1);
	if (and_or == 2 && exit_code != 0)
		return (1);
	return (0);
}
