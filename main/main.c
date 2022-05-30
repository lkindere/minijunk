/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:19:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/30 20:20:11 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"
#include "subshell.h"

//Sets the command in/out to pipe fd, resets pipe fds to -1
void	pipe_fds(t_data *data)
{
	t_cmd *cmd;

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
	// printf("data input: %s\n", data->input);
	// sleep(1);
	// printf("\n\n");
	// printf("Init p1: %d, %d, p2: %d, %d\n", data->pipe1[0], data->pipe1[1], data->pipe2[0], data->pipe2[1]);
	data->input = expander(data->input, data, 0); //Maybe change to char ** and return error codes
	lexer(data);
	parser(data);
	if (!input_is_empty(data->input))
	{
		do_heredoc(data);
		in_out_std(data);
		pipe_fds(data);
	}
	// printf("And_or: %d, exit_code: %d\n", data->and_or, exit_code(-1));
	if (can_execute(data->and_or, exit_code(-1)))
		executer(data, data->cmds);
	else if (data->is_fork)
	{
		terminator(&data);
		exit(0);
	}
	reset_data(data);
	return (0);
}

int	the_loop(char **input, char **segment, t_data *data)
{
	while (true)
	{
		if (handle_and_or(segment, &data->and_or) != 0)
			{;}
		if (is_start(*segment))
			break ;
		if (splitter(data, input, segment) != 0)
			{;}
		if (is_subshell(segment) == 1)
		{
			create_subshells(data, input, segment);
			continue ;
		}
		if ((!(*input) || input_is_empty(*input)) && !(*segment))
		{
			reset_data(data);
			if (data->is_fork && terminator(&data))
				exit (exit_code(-1));
			return (0);
		}
	}
	data->input = (*segment);
	(*segment) = NULL;
	do_stuff(data);
	if (data->is_fork && !(*input) && terminator(&data))
		exit (exit_code(-1));
	return (0);
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
