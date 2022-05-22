/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:21:45 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/22 23:51:30 by lkindere         ###   ########.fr       */
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
int	init_data(t_data **data, char **envp, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	(*data) = ft_calloc(1, sizeof(t_data));
	if (*data == NULL)
		return (MALLOC_FAIL);
	(*data)->envp = clone_envp(envp);
	(*data)->pwd = getcwd((*data)->pwd, 0);
	// (*data)->tokens = new_token();//		probably don't need this, instead will create new tokens as needed.
	// if ((*data)->tokens == NULL)
	// 	return (ft_err(MALLOC_FAIL));
	(*data)->std_in = dup(STDIN_FILENO);
	(*data)->std_out = dup(STDOUT_FILENO);
	(*data)->next = NULL;
	return (0);
}
