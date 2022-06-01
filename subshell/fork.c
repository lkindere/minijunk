/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:45:50 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/31 20:47:34 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subshell.h"

//Initializes the sub process
static void	init_fork(t_data *data, char **input, char**segment)
{
	data->is_fork = 1;
	data->start_code = exit_code(-1);
	if (*input)
		free(*input);
	(*input) = (*segment);
	(*segment) = NULL;
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
	if (pid == 0)
		init_fork(data, input, segment);
	if (pid != 0)
	{
		free(*segment);
		(*segment) = NULL;
		exit_code(get_exitstatus(pid));
	}
	return (0);
}
