/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:26 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 17:11:35 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

//Closes fd and sets the pointer to -1
//Returns 1 on errors
//Returns 0 on success
static int	reset_pipe(int *fd)
{
	if (close(*fd) == -1)
	{
		(*fd) = -1;
		return (1);
	}
	(*fd) = -1;
	return (0);
}

//Closes the appropriate ends of the pipe for main
//Returns 1 on errors
//Returns 0 on success
int	handle_pipe_main(t_data *data)
{
	if (is_first_link(data))
		return (reset_pipe(&data->pipe1[1]));
	if (no_further_pipe(data) == 1)
		return (reset_pipe(&data->pipe1[0]));
	if (no_further_pipe(data) == 2)
		return (reset_pipe(&data->pipe2[0]));
	if (is_further_pipe(data) == 1)
	{
		if (reset_pipe(&data->pipe1[0]) == -1)
			return (1);
		return (reset_pipe(&data->pipe2[1]));
	}
	if (is_further_pipe(data) == 2)
	{
		if (reset_pipe(&data->pipe2[0]) == -1)
			return (1);
		return (reset_pipe(&data->pipe1[1]) == -1);
	}
	return (0);
}

//Closes the appropriate ends of the pipe for fork
//Returns 1 on errors
//Returns 0 on success
int	handle_pipe_fork(t_data *data)
{
	if (is_first_link(data) && reset_pipe(&data->pipe1[0]) == -1)
		return (1);
	if (is_further_pipe(data) == 1)
		return (reset_pipe(&data->pipe2[0]));
	if (is_further_pipe(data) == 2)
		return (reset_pipe(&data->pipe1[0]));
	return (0);
}
