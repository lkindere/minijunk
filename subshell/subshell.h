/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:59:33 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/24 15:35:29 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSHELL_H
# define SUBSHELL_H

#include "../include/parser.h"

typedef struct s_flag
{
	int p_open;
	int p_close;
	int s_quote;
	int d_quote;
} t_flag;

//Utils
int		is_start(const char *input);
int		first_token(const char *input);
void    init_flag(t_flag *flag);
int 	is_quoted(t_flag flag);
void	set_flag(int c, t_flag *flag);

//Utils 2
int		can_execute(int and_or, int exit_code);

#endif