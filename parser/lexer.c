/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:40:22 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/26 13:32:05 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_type	single_type(t_data *data, int *i)
{
	if (data->input[*i] == '|')
		return (PIPE);
	else if (data->input[*i] == '<')
		return (IN);
	else if (data->input[*i] == '>')
		return (OUT);
	else if (data->input[*i] == '\0')
		return (END);
	else if (data->input[*i] == '(')
		return (PAR_OPEN);
	else if (data->input[*i] == ')')
		return (PAR_CLOSE);
	else if (data->input[*i] == '&')
		return (AMPERSAND);
	else
		return (WORD);
}

/*
 *	Skips leading whitespaces and returns type of token.
 *	If it's a two character long token identifier (heredoc or append),
 *	moves i one spot (otherwise it would identify >> to be >> and > tokens).
 */
t_type	get_type(t_data *data, int *i)
{
	while (data->input[*i] == ' ')
		(*i)++;
	if ((data->input[*i] == '<' && data->input[*i + 1] == '<')
			|| (data->input[*i] == '>' && data->input[*i + 1] == '>')
			|| (data->input[*i] == '&' && data->input[*i + 1] == '&')
			|| (data->input[*i] == '|' && data->input[*i + 1] == '|'))
	{
		(*i)++;
		if (data->input[*i - 1] == '<' && data->input[*i] == '<')
			return (HEREDOC);
		else if (data->input[*i - 1] == '>' && data->input[*i] == '>')
			return (APPEND);
		else if (data->input[*i - 1] == '&' && data->input[*i] == '&')
			return (LOG_AND);
		else
			return (LOG_OR);
	}
	else
		return (single_type(data, i));
}

/*
 *	goes through input until it reaches end of token (use ft_tokenlen for that).
 *	When encountering a $, check flags and use add_char to expands[cmd_count]
 *	to save info for executor.
 *	Only save quote chars that are uninterpreted.
 *	iterator <= token_len to also skip the last quote's position with i
 */
void	copy_word(t_data *data, t_token *token, int *i)
{
	int	token_len;
	int	j;

	token_len = ft_tokenlen(data, i);
	j = -1;
	while (++j < token_len)
	{
		if (data->input[*i + j] == '\'' && !data->flags.double_quote)// if quote and that flag is on,
			data->flags.single_quote = 1 - data->flags.single_quote;//just flip it and don't save the quote
		else if (data->input[*i + j] == '\"' && !data->flags.single_quote)
			data->flags.double_quote = 1 - data->flags.double_quote;
		else if (data->input[*i + j] == '$')//encountered a $ sign:
		{
			if (data->flags.single_quote)//inside single quote, so shouldn't be expanded
				add_char(&data->expands[data->cmd_count], '0');//testing, set back to 1 and 0 later
			else//not in single quote, expand
				add_char(&data->expands[data->cmd_count], '1');//testing, set back to 1 and 0 later
			add_char(&(token->content), data->input[*i + j]);//add the $ to the content
		}
		else
			add_char(&(token->content), data->input[*i + j]);//any other char, just save to content
	}
	add_char(&(token->content), '\0');//if input is empty like """", it at least creates an empty string.
	*i = *i + token_len - 1;//was it really just this - 1 that fixed it not finding new tokens that begin right after quote end?
}

void	get_content(t_data *data, t_token *token, int *i)
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
int	new_token(t_data *data, int *i)
{
	t_token	*current;

	current = create_new_token();
	current->type = get_type(data, i);
	get_content(data, current, i);
	token_add_back(&(data->tokens), current);
	if (check_if_new_cmd(data))
	{
		if (data->expands[data->cmd_count] == NULL)
			data->expands[data->cmd_count] = ft_strdup("");
		data->cmd_count++;
		data->dollar_count = 0;
		add_char_ptr(&data->expands);
	}
	// printf("type %i\tcontent: %s\tcommand: %i\n", token_last(data->tokens)->type, token_last(data->tokens)->content, data->cmd_count);
	return (0);
}

int	lexer(t_data *data)
{
	int		i;

	i = -1;
	while (data->input[++i])
	{
		new_token(data, &i);
	}
	new_token(data, &i);
	return (0);
}
