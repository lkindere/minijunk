/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:59:33 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/01 22:48:11 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSHELL_H
# define SUBSHELL_H

# include "main.h"

typedef struct s_flag
{
	int	p_open;
	int	p_close;
	int	s_quote;
	int	d_quote;
}	t_flag;

//Loop
int		splitter(char **input, char **segment);
int		handle_and_or(char **segment, int *and_or);
int		is_subshell(char **segment);
int		create_subshells(t_data *data, char **input, char **segment);

//Utils
int		is_quoted(t_flag flag);
int		is_start(const char *input);
void	init_flag(t_flag *flag);
void	set_flag(int c, t_flag *flag);
int		can_execute(int and_or, int exit_code);

//Utils sep
int		is_separator(int c);
int		split_separator(int c, t_flag flag);
int		remove_separator(char **segment, int i);
int		input_is_empty(char	*input);

#endif