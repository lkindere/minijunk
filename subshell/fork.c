/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:45:50 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 16:46:24 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"

//Closes fd and sets the pointer to -1
int	reset_pipe(int *fd)
{
	if (close(*fd) == -1)
	{
		(*fd) = -1;
		return (1);
	}
	(*fd) = -1;
	return (0);
}

//Check if there's further pipes
//Returns 1 if pipe1 is not closed
//Returns 2 if pipe2 is not closed
int	is_further_pipe(t_data *data)
{
	if (data->pipe1[0] >= 0 && data->pipe1[1] == -1)
	{
		if (data->pipe2[0] >= 0 && data->pipe2[1] >= 0)
			return (1);
	}
	if (data->pipe2[0] >= 0 && data->pipe2[1] == -1)
	{
		if (data->pipe1[0] >= 0 && data->pipe1[1] >= 0)
			return (2);
	}
	return (0);
}

//Checks if there are no further pipes
int	no_further_pipe(t_data *data)
{
	if (data->pipe1[0] >= 0 && data->pipe1[1] == -1)
	{
		if (data->pipe2[0] == -1 && data->pipe2[1] == -1)
			return (1);
	}
	if (data->pipe2[0] >= 0 && data->pipe2[1] == -1)
	{
		if (data->pipe1[0] == -1 && data->pipe1[1] == -1)
			return (2);
	}
	return (0);
}

//Checks if it is the first link of the pipe chain
int	is_first_link(t_data *data)
{
	if (data->pipe1[0] >= 0 && data->pipe1[1] >= 0)
	{
		if (data->pipe2[0] == -1 && data->pipe2[1] == -1)
			return (1);
	}
	return (0);
}

int	handle_pipe_main(t_data *data)
{
	if (is_first_link(data))
	{
		if (reset_pipe(&data->pipe1[1]) == -1)
			return (1);
		return (0);
	} 
	if (no_further_pipe(data) == 1)
	{
		if (reset_pipe(&data->pipe1[0]) == -1)
			return (1);
		return (0);
	}
	if (no_further_pipe(data) == 2)
	{
		if (reset_pipe(&data->pipe2[0]) == -1)
			return (1);
		return (0);
	}
	if (is_further_pipe(data) == 1)
	{
		if (reset_pipe(&data->pipe1[0]) == -1)
			return (1);
		if (reset_pipe(&data->pipe2[1]) == -1)
			return (1);
		return (0);
	}
	if (is_further_pipe(data) == 2)
	{
		if (reset_pipe(&data->pipe2[0]) == -1)
			return (1);
		if (reset_pipe(&data->pipe1[1]) == -1)
			return (1);
		return (0);
	}
	return (0);
}

int	handle_pipe_fork(t_data *data)
{
	if (is_first_link(data) && reset_pipe(&data->pipe1[0]) == -1)
		return (1);
	if (is_further_pipe(data) == 1)
	{
		if (reset_pipe(&data->pipe2[0]) == -1)
			return (1);
		return (0);
	}
	if (is_further_pipe(data) == 2)
	{
		if (reset_pipe(&data->pipe1[0]) == -1)
			return (1);
		return (0);
	}
	return (0);
}

void	init_fork(t_data *data, char **input, char**segment)
{
	data->is_fork = 1;
	if (*input)
		free(*input);
	(*input) = (*segment);
	(*segment) = NULL;
}

int	handle_pipes(t_data *data, int pid)
{
	if (pid != 0)
		return (handle_pipe_main(data));
	if (pid == 0)
		return (handle_pipe_fork(data));
	return (0);
}

//Creates subshells
//Returns 1 on error
int	create_subshells(t_data *data, char **input, char **segment)
{
	int	pid;

	// printf("Fork segment: %s\n", (*segment));
	pid = fork();
	if (pid == -1)
		return (1);
	handle_pipes(data, pid);
	if (pid == 0)
		init_fork(data, input, segment);
	if (pid != 0)
	{
		free(*segment);
		(*segment) = NULL;
		// printf("Main waiting: pipe1 in: %d, pipe1 out: %d, pipe2 in: %d, pipe2 out: %d\n\n", data->pipe1[0], data->pipe1[1], data->pipe2[0], data->pipe2[1]);
		data->exit_code = get_exitstatus(pid);
	}
	// printf("Pipes after fork:\n");
	// printf("Is fork: %d, pipe1 in: %d, pipe1 out: %d, pipe2 in: %d, pipe2 out: %d\n\n", data->is_fork, data->pipe1[0], data->pipe1[1], data->pipe2[0], data->pipe2[1]);
	return (pid);
}

// pipe1		 pipe2
// 1 	2		-1	-2	if first link in pipe
// sub:
// -1	2		-1	-2	
// main:
// 1	-2		-1	-2

// pipe1		pipe2
// 1	-2		1	2	if further pipes 
// sub:
// 1	-2		-1	2
// main:
// -1	-2		1	-2 > open new pipe
// 1	2

// pipe1		pipe2
// 1	2		1	-2	if further pipes reversed
// sub:
// -1	2		1	-2
// main:
// 1	-2		-1	-2	> open new pipe
// 			1	2

// pipe1		 pipe2								
// 1	-2		-1	-2	if no further pipe
// sub:
// 1	-2		-1	-2
// main:
// -1	-2		-1	-2

// pipe1		pip2
// -1	-2		1	-2	if no further pipes reversed
// sub:
// -1	-2		1	-2
// main:
// -1	-2		-1	-2		