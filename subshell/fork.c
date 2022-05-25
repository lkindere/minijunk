/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:45:50 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/25 17:13:05 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

//Initializes the sub process
static void	init_fork(t_data *data, char **input, char**segment)
{
	data->is_fork = 1;
	if (*input)
		free(*input);
	(*input) = (*segment);
	(*segment) = NULL;
}

//Splits to handle_pipe_main / handle_pipe_fork
//Returns 1 on errors
//Returns 0 on success
static int	handle_pipes(t_data *data, int pid)
{
	if (pid != 0)
		return (handle_pipe_main(data));
	if (pid == 0)
		return (handle_pipe_fork(data));
	return (0);
}

//Creates subshells
//Returns 1 on error
//Returns 0 on success
int	create_subshells(t_data *data, char **input, char **segment)
{
	int	pid;

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
		data->exit_code = get_exitstatus(pid);
	}
	return (0);
}
