/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:54:56 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/22 15:16:13 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	found_heredoc(t_cmd *cmd, t_token *token)
{
	char	*input;
	char	*str;
	int		fd[2];

	input = NULL;
	str = NULL;
	if (cmd->in >= 0 && close(cmd->in) != 0)
		return (ft_err(ERROR_PIPE));
	if (pipe(fd) != 0)
		return (ft_err(ERROR_PIPE));
	while (ft_strcmp_x(input, token->content, ft_strlen(token->content)) != 0)//compares input with EOF from heredoc.
	{
		input = readline("> ");
		if (!input)
			return (0);
		if (ft_add_str(&str, input) != 0)
			return (ft_err(MALLOC_FAIL));
		if (ft_add_str(&str, "\n") != 0)
			return (ft_err(MALLOC_FAIL));
	}
	write(fd[1], str, ft_strlen(str) - ft_strlen(token->content) - 1);//-1 for the last "\n" after the EOF.
	if (close(fd[1]) != 0)
		return (ft_err(ERROR_PIPE));
	cmd->in = fd[0];
	return (0);
}

int	do_heredoc(t_data *data)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = data->cmds;
	token = data->tokens;
	while (token && token->type != END)
	{
		if (token->type == PIPE)
			cmd = cmd->pipe_next;
		else if (token->type == HEREDOC)
		{
			if (found_heredoc(cmd, token) != 0)
				return (1);
		}
		token = token->next;
	}
	return (0);
}
