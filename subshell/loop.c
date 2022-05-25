/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:05:09 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 16:30:49 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"
#include "subshell.h"

int	do_stuff(t_data *data)
{
	data->input = expander(data->input, data); //Maybe change to char ** and return error codes

	lexer(data);
	parser(data);
	do_heredoc(data);
	in_out_std(data);
	if (data->pipe1[0] != -1)
	{
		data->cmds->in = data->pipe1[0];
		data->pipe1[0] = -1;
	}
	if (data->pipe1[1] != -1)
	{
		data->cmds->out = data->pipe1[1];
		data->pipe1[1] = -1;
	}
	if (data->pipe2[0] != -1)
	{
		data->cmds->in = data->pipe2[0];
		data->pipe2[0] = -1;
	}
	if (data->pipe2[1] != -1)
	{
		data->cmds->out = data->pipe2[1];
		data->pipe2[1] = -1;
	}
	// printf("\nData->and_or: %d with exit code: %d\n", data->and_or, data->exit_code);;
	if (can_execute(data->and_or, data->exit_code))
	{
		// printf("Executing cmd: %s in fd: %d, out fd: %d\n", data->cmds->cmd_arg[0], data->cmds->in, data->cmds->out);
		// printf("\nvvv\n");
		executer(data, data->cmds);
		// printf("^^^\n");
	}
	//Everytime reset data occurs should be cmd | (cmd) or (cmd) | cmd, meaning always singe pipe exec from main, maybe close pipes in data?
	reset_data(data);
	// printf("\n----------------------------------------------------------------\n");
	return (0);
}

int	the_loop(char **input, char **segment, t_data *data)
{
	while (true)
	{
		if (handle_separators(data, segment, &data->and_or) != 0)
			;
		if (is_start(*segment))
			break ;
		if (splitter(data, input, segment) != 0)
			;
		// printf("Segment after splitter: %s\n", *segment);
		// printf("Pipes after splitter:\n");
		// printf("pipe1 in: %d, pipe1 out: %d\npipe2 in: %d, pipe2 out: %d\n\n", data->pipe1[0], data->pipe1[1], data->pipe2[0], data->pipe2[1]);
		if (is_subshell(segment) == 1)
		{
			create_subshells(data, input, segment);
			// printf("Subshell started with: %s\n", *input);
			// printf("Pipes after subshell:\n");
			// printf("pipe1 in: %d, pipe1 out: %d\npipe2 in: %d, pipe2 out: %d\n\n", data->pipe1[0], data->pipe1[1], data->pipe2[0], data->pipe2[1]);
			continue ;
		}
		// printf("Post subshell segment: %s, is fork: %d\n\n", *segment, data->is_fork);

		// printf("----------------------------------------------------\n");
		// printf("Remaining input: %s\n", *input);
		if ((!(*input) || input_is_empty(*input)) && !(*segment))
		{
			reset_data(data);
			if (data->is_fork)
				exit (data->exit_code);
			return (0);
		}
	}
	// printf("Returning from loop, pipe1 in: %d, pipe1 out: %d, pipe2 in: %d, pipe2 out: %d\n\n", data->pipe1[0], data->pipe1[1], data->pipe2[0], data->pipe2[1]);
	data->input = (*segment);
	(*segment) = NULL;
	do_stuff(data);

	if (data->is_fork && !(*input))
	{
		// printf("FORK EXITTED with exit code %d\n", data->exit_code);
		exit (data->exit_code);
	}
}