/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:25:53 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/11 16:10:50 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 *	Checks if the passed char is an interpreted metacharacter or end of input.
 *	Needs data struct to know about the quote flags.
 */
int	is_end_of_token(t_data *data, char c)
{
	if (c == '\0')
		return (1);
	if (!(data->flags.single_quote || data->flags.double_quote) && is_meta(c))
		return (1);
	return (0);
}

t_token	*create_new_token(void)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->type = NONE;
	new->content = NULL;
	new->next = NULL;
	return (new);
}

/*
 *	returns pointer to last element of linked list
 */
t_token	*token_last(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

/*
 *	Adds the token 'new' to the back of the linked list passed by address
 *	as 'list'. If the list doesn't exist yet, 'new' will be the start of it.
 */
void	token_add_back(t_token **list, t_token *new)
{
	if (*list == NULL)
		*list = new;
	else
		token_last(*list)->next = new;
}

/*
 *	Returns 1 if last token is a pipe and therefore a new command will start.
 *	Otherwise returns 0.
 */
int	check_if_new_cmd(t_data *data)
{
	if (token_last(data->tokens)->type == PIPE)
		return (1);
	return (0);
}
