/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:49:46 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 16:50:40 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

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
