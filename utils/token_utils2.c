/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:12:00 by mmeising          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/26 17:42:16 by mmeising         ###   ########.fr       */
=======
/*   Updated: 2022/05/26 13:20:10 by lkindere         ###   ########.fr       */
>>>>>>> b6d4d548aecc0c9a038ff2209cfe83e0e8e25fbe
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 *	Returns length until token ends (interpreted metacharacter) or end of input.
 *	If int i is passed as address of start index, takes that as start point 
 *	from which to start counting the length of the token (not setting
 *	it to the end).
 */
int	ft_tokenlen(t_data *data, int *i)
{
	t_flags	temp;
	int		len;
	int		j;

	temp = data->flags;
	j = 0;
	if (i)
		j = *i;
	while (data->input[j])
	{
		if (!data->flags.double_quote && data->input[j] == '\'')
			data->flags.single_quote = 1 - data->flags.single_quote;
		if (!data->flags.single_quote && data->input[j] == '\"')
			data->flags.double_quote = 1 - data->flags.double_quote;
		if (is_end_of_token(data, data->input[j]))
			break ;
		j++;
	}
	len = j;
	if (i)
		len = j - *i;
	data->flags = temp;
	return (len);
}

/*
 *	Deletes the token sent by address of it.
 *	If there is content, free()'s that and sets it to NULL.
 *	free()'s the token and sets it to NULL.
 */
void	del_token(t_token **token)
{
	if ((*token)->content)
	{
		free((*token)->content);
		(*token)->content = NULL;
	}
	free(*token);
	*token = NULL;
}

/*
 *	Returns 1 if input type is any redirection type, otherwise returns 0.
 */
int	is_redir(t_type type)
{
	return (type == IN || type == OUT || type == HEREDOC || type == APPEND);
}

/*
 *	Deletes the token next in the list and links the rest of the list
 *	to the token passed.
 */
void	del_next_token(t_token *token)
{
	t_token	*temp;

	temp = NULL;
	if (token->next->next)
		temp = token->next->next;
	del_token(&(token->next));
	token->next = temp;
}

/*
 *	Returns 1 if c equals ' ', '|', '<', '>', '(', ')'
 *	(spacebar, pipe, less than, greater than, parenthesis open/close).
 */
int	is_meta(char c)
{
	return (c == ' ' || c == '|' || c == '<' || c == '>' || c == '('
		|| c == ')' || c == '&' || (c >= 9 && c <= 13));
}
