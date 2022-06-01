/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:19:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/01 21:13:55 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"
#include "subshell.h"

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
	}
	// printf("Data input: %s\n", data->input);
	if (can_execute(data->and_or, exit_code(-1)))
		executer(data, data->cmds);
	reset_data(data);
	return (0);
}

int	subsheller(char **input, char **segment, t_data *data)
{
	if (data->is_fork)
		data->start_code = -1;
	data->input = (*segment);
	(*segment) = NULL;
	do_stuff(data);
	if (data->is_fork)
		exit(0);
	if (data->is_fork && !(*input) && terminator(&data))
		exit (exit_code(-1));
	return (0);
}

int	the_loop(char **input, char **segment, t_data *data)
{
	while (1)
	{
		if (handle_and_or(data, segment, &data->and_or) != 0)
			return (1);
		if (is_start(*segment))
			break ;
		if (splitter(input, segment) != 0)
			return (1);
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
