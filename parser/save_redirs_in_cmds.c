/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_redirs_in_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 03:46:23 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/27 13:16:49 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	type_in(t_token *temp, t_cmd *cmd)
{
	if (cmd->in != -2)
		close(cmd->in);
	cmd->in = open(temp->content, O_RDONLY, 0644);
	if (cmd->in == -1)
	{
		perror(temp->content);
		return (1);
	}
	return (0);
}

static int	type_out(t_token *temp, t_cmd *cmd)
{
	if (cmd->out != -2)
		close(cmd->out);
	cmd->out = open(temp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->out == -1)
	{
		perror(temp->content);
		return (1);
	}
	return (0);
}

static int	type_append(t_token *temp, t_cmd *cmd)
{
	if (cmd->out != -2)
		close(cmd->out);
	cmd->out = open(temp->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->out == -1)
	{
		perror(temp->content);
		return (1);
	}
	return (0);
}

void	save_redirs_in_cmds(t_data *data)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = data->tokens;
	cmd = data->cmds;
	while (temp && temp->type != END)
	{
		if (temp->type == PIPE)
		{
			cmd = cmd->pipe_next;
			temp = temp->next;
		}
		else if ((temp->type == IN && type_in(temp, cmd) != 0)
				|| (temp->type == OUT && type_out(temp, cmd) != 0)
				|| (temp->type == APPEND && type_append(temp, cmd) != 0))
		{//one of the redirections failed
			while (temp && temp->type != PIPE && temp->type != END)
				temp = temp->next;
		}
		else
			temp = temp->next;
		// else if (temp->type == OUT && type_out(temp, cmd) != 0)
		// 	;
		// else if (temp->type == APPEND && type_append(temp, cmd) != 0)
		// 	;
		// temp = temp->next;
	}
}
