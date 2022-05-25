/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:21:45 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/25 14:47:08 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 *	Initializes data.
 *	Calloc's data struct, saves envp inside.
 *	Saves a NULL-pointer for data->cmds[0] for easier realloc later.
 *
 *	argc and argv added to silence warning of not using argc/argv in main.
 */
int	init_data(t_data **data, char **envp)
{
	(*data) = ft_calloc(1, sizeof(t_data));
	(*data)->cmds = ft_calloc(1, sizeof(t_cmd));
	if ((*data)->cmds == NULL)
		return (ft_err(MALLOC_FAIL));
	if (*data == NULL)
		return (MALLOC_FAIL);
	(*data)->envp = clone_envp(envp);
	(*data)->pwd = getcwd((*data)->pwd, 0);
	(*data)->std_in = dup(STDIN_FILENO);
	(*data)->std_out = dup(STDOUT_FILENO);
	if (add_char_ptr(&(*data)->expands) != 0)
		return (MALLOC_FAIL);
	(*data)->pipe1[0] = -1;
	(*data)->pipe1[1] = -1;
	(*data)->pipe2[0] = -1;
	(*data)->pipe2[1] = -1;
	(*data)->is_fork = 0;
	return (0);
}
