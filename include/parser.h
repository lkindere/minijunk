/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:34:44 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/26 19:59:33 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "main.h"

int		create_cmd_args(t_data *data);
void	save_redirs_in_cmds(t_data *data);
int		do_heredoc(t_data *data);
void	in_out_std(t_data *data);

int		add_char_ptr(char ***arr);
int		add_char(char **str, char c);
int		ft_add_str(char **str, char *add);

/*	lexer						*/

t_type	get_type(t_data *data, int *i);

/*	parser						*/
int		check_invalid_words_amp(t_data *data);
int		check_content_between_par(t_data *data);
int		check_even_par_count(t_data *data);
int		check_input_each_cmd(t_data *data);

/*	token utils					*/
int		is_end_of_token(t_data *data, char c);
t_token	*create_new_token(void);
t_token	*token_last(t_token *token);
void	token_add_back(t_token **list, t_token *new);
int		check_if_new_cmd(t_data *data);

int		ft_tokenlen(t_data *data, int *i);
void	del_token(t_token **token);
int		is_redir(t_type type);
void	del_next_token(t_token *token);

/*	debug						*/

void	debug_print_expands(t_data *data);
void	debug_print_tokens(t_data *data);
void	debug_print_cmds(t_data *data);

#endif