/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:45:50 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/24 18:56:14 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"

//Creates subshells
//Returns 1 on error
int	create_subshells(t_data *data, char **input, char **segment, int and_or)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		data->is_fork = 1;
		data->and_or = and_or;
		// printf("\n\nInitial and_or on sub: %d\n\n", data->and_or);
		if (*input)
			free(*input);
		(*input) = (*segment);
		(*segment) = NULL;
	}
	if (pid != 0)
	{
		free(*segment);
		(*segment) = NULL;
		data->exit_code = get_exitstatus(pid);
	}
	return (pid);
}
