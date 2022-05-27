/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:19:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/27 16:31:02 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"
#include "subshell.h"

//Sets the command in/out to pipe fd, resets pipe fds to -1
void	pipe_fds(t_data *data)
{
	if (data->pipe1[0] != -1)
		data->cmds->in = data->pipe1[0];
	if (data->pipe1[1] != -1)
		data->cmds->out = data->pipe1[1];
	if (data->pipe2[0] != -1)
		data->cmds->in = data->pipe2[0];
	if (data->pipe2[1] != -1)
		data->cmds->out = data->pipe2[1];
	data->pipe1[0] = -1;
	data->pipe1[1] = -1;
	data->pipe2[0] = -1;
	data->pipe2[1] = -1;
}

void	print_command_data(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("Args: ");
	while (cmd->cmd_arg && cmd->cmd_arg[i])
		printf("%s, ", cmd->cmd_arg[i++]);
	printf("\n");
	printf("In: %d, out: %d\n", cmd->in, cmd->out);
	printf("Pipe prev: %p, pipe next: %p\n", cmd->pipe_prev, cmd->pipe_next);
}

//Returns the entire chain of commands for current segment
int	do_stuff(t_data *data)
{
	data->input = expander(data->input, data); //Maybe change to char ** and return error codes
	if (input_is_empty(data->input))
		return (reset_data(data));
	printf("Data input: %s\n", data->input);
	lexer(data);
	parser(data);
	do_heredoc(data);
	in_out_std(data);
	pipe_fds(data);
	if (can_execute(data->and_or, data->exit_code))
		executer(data, data->cmds);
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
			if (data->is_fork)
				exit (data->exit_code);
			return (0);
		}
	}
	data->input = (*segment);
	(*segment) = NULL;
	do_stuff(data);
	if (data->is_fork && !(*input))
		exit (data->exit_code);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*full_input;
	char	*segment;
	t_data	*data;

	segment = NULL;
	signal_handler();
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
