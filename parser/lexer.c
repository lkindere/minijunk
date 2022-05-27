/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:40:22 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/27 19:38:59 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 *	goes through input until it reaches end of token (use ft_tokenlen for that).
 *	When encountering a $, check flags and use add_char to expands[cmd_count]
 *	to save info for executor.
 *	Only save quote chars that are uninterpreted.
 *	iterator <= token_len to also skip the last quote's position with i
 */
static void	copy_word(t_data *data, t_token *token, int *i)
{
	int	token_len;
	int	j;

	token_len = ft_tokenlen(data, i);
	j = -1;
	while (++j < token_len)
	{
		if (data->input[*i + j] == '\'' && !data->flags.double_quote)
			data->flags.single_quote = 1 - data->flags.single_quote;
		else if (data->input[*i + j] == '\"' && !data->flags.single_quote)
			data->flags.double_quote = 1 - data->flags.double_quote;
		else if (data->input[*i + j] == '*')
		{
			if (data->flags.single_quote || data->flags.double_quote)
				add_char(&data->expands[data->cmd_count], '0');
			else//not in quotes, expand
				add_char(&data->expands[data->cmd_count], '1');
			add_char(&(token->content), data->input[*i + j]);
		}
		else
			add_char(&(token->content), data->input[*i + j]);
	}
	add_char(&(token->content), '\0');
	*i = *i + token_len - 1;//was it really just this - 1 that fixed it not finding new tokens that begin right after quote end?
}

/*
 *	Sets content depending on type of token, 
 *	if WORD it copies the word from input.
 */
static void	get_content(t_data *data, t_token *token, int *i)
{
	if (token->type == PIPE)
		token->content = ft_strdup("|");
	else if (token->type == IN)
		token->content = ft_strdup("<");
	else if (token->type == HEREDOC)
		token->content = ft_strdup("<<");
	else if (token->type == OUT)
		token->content = ft_strdup(">");
	else if (token->type == APPEND)
		token->content = ft_strdup(">>");
	else if (token->type == END)
		token->content = ft_strdup("newline");
	else if (token->type == PAR_OPEN)
		token->content = ft_strdup("(");
	else if (token->type == PAR_CLOSE)
		token->content = ft_strdup(")");
	else if (token->type == LOG_AND)
		token->content = ft_strdup("&&");
	else if (token->type == LOG_OR)
		token->content = ft_strdup("||");
	else if (token->type == AMPERSAND)
		token->content = ft_strdup("&");
	else
		copy_word(data, token, i);
}

/*
 *	Creates a new empty token, gets the type and content from input and appends
 *	the token to the end of the token linked list.
 *	While going through the input, it also sets the expands flags if it
 *	encounters $-signs.
 *	If the token is of type PIPE, so it starts a new command, the function
 *	fills the according expands pointer with an empty string instead of NULL.
 */
static int	new_token(t_data *data, int *i)
{
	t_token	*current;

	current = create_new_token();
	if (current == NULL)
		return (internal_error_return(ERROR_MALLOC));
	current->type = get_type(data, i);
	get_content(data, current, i);
	if (current->content == NULL)
		return (internal_error_return(ERROR_MALLOC));
	token_add_back(&(data->tokens), current);
	if (data->expands[data->cmd_count] == NULL)
		data->expands[data->cmd_count] = ft_strdup("");
	if (data->expands[data->cmd_count] == NULL)
		return (internal_error_return(ERROR_MALLOC));
	if (check_if_new_cmd(data))
	{
		data->cmd_count++;
		data->dollar_count = 0;
		if (add_char_ptr(&data->expands) != 0)
			return (internal_error_return(ERROR_MALLOC));
	}
	return (0);
}

int	lexer(t_data *data)
{
	int		i;

	i = -1;
	while (data->input[++i])
	{
		if (new_token(data, &i) != 0)
			return (ERROR_MALLOC);
	}
	if (new_token(data, &i) != 0)
		return (ERROR_MALLOC);
	return (0);
}
