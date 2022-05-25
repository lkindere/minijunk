/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:28:45 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/25 18:47:31 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// int	ft_err(t_error err)
// {
// 	if (err == MALLOC_FAIL)
// 		ft_putstr_fd("malloc failed\n", STDERR_FILENO);
// 	else if (err == ERROR_PIPE)
// 		ft_putstr_fd("pipe failed\n", STDERR_FILENO);
// 	else if (err)
// 		ft_putstr_fd("general error\n", STDERR_FILENO);
// 	return (err);
// }

/*
 *	Throws syntax error at token passed as input
 */
int	ft_syntax_err(char *token)
{
	char	*str;

	str = ft_strdup(PROMPT": syntax error near unexpected token `");
	ft_add_str(&str, token);
	ft_add_str(&str, "\'\n");
	ft_putstr_fd(str, STDERR_FILENO);
	return (1);
}

/*
 *	Throws "blank" error at token passed as input.
 */
// int	ft_blank_err_near(char *blank, char *token)
// {
// 	char	*str;

// 	str = ft_strdup(PROMPT": ");
// 	ft_add_str(&str, blank);
// 	ft_add_str(&str, " error near unexpected token `");
// 	ft_add_str(&str, token);
// 	ft_add_str(&str, "\'\n");
// 	ft_putstr_fd(str, STDERR_FILENO);
// 	return (1);
// }
