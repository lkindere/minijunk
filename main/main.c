/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:19:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/31 17:16:21 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"
#include "subshell.h"

//Sets the command in/out to pipe fd, resets pipe fds to -1
void	pipe_fds(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	while (cmd)
	{
		if (data->pipe1[1] != -1)
			cmd->out = data->pipe1[1];
		if (data->pipe2[1] != -1)
			cmd->out = data->pipe2[1];
		cmd = cmd->pipe_next;
	}
	if (data->pipe1[0] != -1)
		data->cmds->in = data->pipe1[0];
	if (data->pipe2[0] != -1)
		data->cmds->in = data->pipe2[0];
	data->pipe1[0] = -1;
	data->pipe2[0] = -1;
}

//Returns the entire chain of commands for current segment
int	do_stuff(t_data *data)
{
	data->input = expander(data->input, data, 0);
	lexer(data);
	parser(data);
	if (!input_is_empty(data->input))
	{
		do_heredoc(data);
		in_out_std(data);
		pipe_fds(data);
	}
	if (can_execute(data->and_or, exit_code(-1)))
		executer(data, data->cmds);
	reset_data(data);
	return (0);
}

int	subsheller(char **input, char **segment, t_data *data)
{
	data->input = (*segment);
	(*segment) = NULL;
	// printf("do\n");
	do_stuff(data);
	if (data->is_fork && !(*input) && terminator(&data))
		exit (exit_code(-1));
	return (0);
}

int	the_loop(char **input, char **segment, t_data *data)
{
	while (1)
	{
		// printf("Segment: %s, \ninput: %s\n\n", *segment, *input);
		if (handle_and_or(data, segment, &data->and_or) != 0)
			return (1);
		// printf("And or Segment: %s, \ninput: %s\n\n", *segment, *input);
		if (is_start(*segment))
			break ;
		if (splitter(data, input, segment) != 0)
			return (1);
		// printf("Splitter Segment: %s, \ninput: %s\n\n", *segment, *input);
		if (is_subshell(segment) == 1 && create_subshells(data, input, segment))
			continue ;
		if ((!(*input) || input_is_empty(*input)) && !(*segment))
		{
			if (data->is_fork && terminator(&data))
				exit (exit_code(-1));
			reset_data(data);
			return (0);
		}
	}
	// printf("Segment: %s\n", *segment);
	return (subsheller(input, segment, data));
}

int	main(int argc, char **argv, char **envp)
{
	char	*full_input;
	char	*segment;
	t_data	*data;

	full_input = NULL;
	segment = NULL;
	if (init_data(&data, envp) != 0)
		internal_error_return(ERROR_MALLOC);
	while (argc || argv)
	{
		while (!full_input)
			get_input(&full_input, data);
		if (syntax_check(data, &full_input) != 0)
			continue ;
		while (is_input(full_input, segment))
			the_loop(&full_input, &segment, data);
	}
	return (0);
}
