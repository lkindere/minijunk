/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 04:39:25 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/26 16:35:22 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 *	Creates a new cmd struct, links it to the end of the cmds linked list and
 *	sets the cmds pointer to the new cmd struct.
 *	Allocates 2 pointers size to cmd_arg. One for first input and
 *	one for terminating NULL pointer. So first one can be overwritten with
 *	ft_strdup.
 *	in and out fds are set to -1 to show they are not yet set.
 */
static int	create_new_cmd(t_cmd **cmd)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (new_cmd == NULL)
		return (internal_error_return(ERROR_MALLOC));
	new_cmd->cmd_arg = NULL;
	new_cmd->in = -2;
	new_cmd->out = -2;
	(*cmd)->pipe_next = new_cmd;
	new_cmd->pipe_next = NULL;
	new_cmd->pipe_prev = (*cmd);
	(*cmd) = (*cmd)->pipe_next;
	return (0);
}

/*
 *	returns index of first NULL pointer in char **ptr_arr
 */
int	ft_last_ptr(char **ptr_arr)
{
	int	i;

	i = 0;
	while (ptr_arr[i])
		i++;
	return (i);
}

/*
 *	Goes through all tokens, creates the cmd linked lists for every command.
 */
int	create_cmd_args(t_data *data)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = data->tokens;
	cmd = data->cmds;
	while (temp && temp->type != END)
	{
		if (temp->type == PIPE)
		{
			if (create_new_cmd(&cmd) != 0)
				return (internal_error_return(ERROR_MALLOC));
		}
		else if (temp->type == WORD)
		{
			add_char_ptr(&cmd->cmd_arg);
			cmd->cmd_arg[ft_last_ptr(cmd->cmd_arg)] = ft_strdup(temp->content);
		}
		temp = temp->next;
	}
	if (cmd->cmd_arg == NULL)
	{
		add_char_ptr(&cmd->cmd_arg);
		ft_add_str(&cmd->cmd_arg[0], "\0");
	}
	return (0);
}
