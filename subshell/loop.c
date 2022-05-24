/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:05:09 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/24 19:28:52 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"
#include "subshell.h"

int	the_loop(char **input, char **segment, t_data *data)
{
	int	and_or_next;

	and_or_next = 0;
	while (true)
	{
		if (splitter(input, segment) != 0)
			;
			//Error reset
		printf("\n\nAfter splitter:\n");
		printf("Segment: %s, data->is_fork: %d\n", *segment, data->is_fork);
		printf("Full input: %s, data->is_fork: %d\n\n", *input, data->is_fork);

		if (is_subshell(segment) == 1)
			create_subshells(data, input, segment, and_or_next);
		printf("Is fork: %d\n", data->is_fork);
		printf("After subshell:\n");
		printf("Segment: %s, is_fork: %d\n", *segment, data->is_fork);
		printf("Full input: %s, is_fork: %d\n\n", *input, data->is_fork);

		if (handle_separators(data, input, &and_or_next) != 0)
			;
			// Error reset
	
		printf("After separator: data->and_or: %d\n", data->and_or);
		printf("Segment: %s, is_fork: %d\n", *segment, data->is_fork);
		printf("Full input: %s, is_fork: %d\n\n", *input, data->is_fork);
		if (!(*input) && !(*segment))
		{
			if (data->is_fork)
				exit (data->exit_code);
			reset_data(data);
			return (0);
		}
		if (is_start(*segment))
			break ;
	}
	// printf("\n");
	// printf("Data exit code: %d, is_fork: %d\n", data->exit_code, data->is_fork);
	// printf("Data and or: %d, is_fork: %d\n", data->and_or, data->is_fork);
	// printf("Data input: %s, is_fork: %d\n", data->input, data->is_fork);
	data->input = (*segment);
	(*segment) = NULL;
	data->input = expander(data->input, data); //Maybe change to char ** and return error codes

	lexer(data);

	parser(data);

	do_heredoc(data);

	in_out_std(data);

	// printf("\nData->and_or: %d\n", data->and_or);
	// printf("Executing with exit code: %d\n", data->exit_code);
	if (can_execute(data->and_or, data->exit_code))
		executer(data, data->cmds);
	reset_data(data);
	data->and_or = and_or_next;
	if (data->is_fork && !(*input))
	{
		// printf("FORK EXITTED with exit code %d\n", data->exit_code);
		exit (data->exit_code);
	}
	// printf("-------------------------------------------------------------------\n");
}