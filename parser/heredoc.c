/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:54:56 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/25 19:16:35 by lkindere         ###   ########.fr       */
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
		return (internal_error_return(ERROR_CLOSE));
	if (pipe(fd) != 0)
		return (internal_error_return(ERROR_PIPE));
	while (ft_strcmp_x(input, token->content, ft_strlen(token->content)) != 0)//compares input with EOF from heredoc.
	{
		input = readline("> ");
		if (!input)
			return (0);
		if (ft_add_str(&str, input) != 0)
			return (internal_error_return(ERROR_MALLOC));
		if (ft_add_str(&str, "\n") != 0)
			return (internal_error_return(ERROR_MALLOC));
	}
	write(fd[1], str, ft_strlen(str) - ft_strlen(token->content) - 1);//-1 for the last "\n" after the EOF.
	if (close(fd[1]) != 0)
		return (internal_error_return(ERROR_CLOSE));
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
