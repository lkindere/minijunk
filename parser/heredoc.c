/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:54:56 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/28 16:30:18 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Reads to str passed by ref
//Expands it
//Returns 1 on error
//Returns 0 on success
int	read_heredoc(t_data *data, t_token *token, char **str)
{
	char	*input;

	input = NULL;
	while (ft_strcmp_x(input, token->content, ft_strlen(token->content)) != 0)
	{
		input = readline("XD: ");
		if (!input || !input[0])
			return (0);
		if (ft_add_str(str, input) != 0 || ft_add_str(str, "\n") != 0)
			return (1);
	}
	*str = expander(*str, data, 1);
	return (0);
}

int	found_heredoc(t_data *data, t_cmd *cmd, t_token *token)
{
	char	*str;
	int		fd[2];

	str = NULL;
	if (cmd->in >= 0 && close(cmd->in) != 0)
		return (internal_error_return(ERROR_CLOSE));
	if (pipe(fd) != 0)
		return (internal_error_return(ERROR_PIPE));
	if (read_heredoc(data, token, &str) != 0)
		return (internal_error_return(ERROR_MALLOC));
	if (!str)
		return (0);
	write(fd[1], str, ft_strlen(str) - ft_strlen(token->content) - 1);
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
			if (found_heredoc(data, cmd, token) != 0)
				return (1);
		}
		token = token->next;
	}
	return (0);
}
