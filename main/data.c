/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:23:20 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/26 17:15:16 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
 *	Reallocates array of strings passed by address to be of size of
 *	count of strings inside + 2.
 *	+ 2 for one new string and the NULL terminator.
 */
int	add_char_ptr(char ***arr)
{
	char	**ret;
	int	i;

	if (*arr == NULL)
	{
		*arr = ft_calloc(2, sizeof(char *));
		if (*arr == NULL)
		return (internal_error_return(ERROR_MALLOC));
	}
	else
	{
		i = 0;
		while ((*arr)[i])
			i++;
		ret = ft_calloc(i + 2, sizeof(char *));
		if (ret == NULL)
			return (internal_error_return(ERROR_MALLOC));
		i = -1;
		while ((*arr)[++i])
			ret[i] = (*arr)[i];
		free(*arr);
		*arr = ret;
	}
	return (0);
}

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
		return (internal_error_return(ERROR_MALLOC));
	if (*data == NULL)
		return (internal_error_return(ERROR_MALLOC));
	(*data)->envp = clone_envp(envp);
	(*data)->pwd = getcwd((*data)->pwd, 0);
	(*data)->std_in = dup(STDIN_FILENO);
	(*data)->std_out = dup(STDOUT_FILENO);
	if (add_char_ptr(&(*data)->expands) != 0)
		return (internal_error_return(ERROR_MALLOC));
	(*data)->pipe1[0] = -1;
	(*data)->pipe1[1] = -1;
	(*data)->pipe2[0] = -1;
	(*data)->pipe2[1] = -1;
	(*data)->is_fork = 0;
	return (0);
}


/*
 *	Resets the data that needs to be cleaned for every time we get new input.
 *	Includes resetting stdin and stdout from the backup saved in data.
 */
int	reset_data(t_data *data)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->cmds)
		free_cmds(&data->cmds);
	data->cmds = ft_calloc(1, sizeof(t_cmd));
	if (data->cmds == NULL)
		return (internal_error_return(ERROR_MALLOC));
	if (data->tokens)
		free_tokens(&data->tokens);
	data->flags.single_quote = 0;
	data->flags.double_quote = 0;
	data->cmd_count = 0;
	data->dollar_count = 0;
	if (data->expands)
		free_2d_char(&data->expands);
	if (add_char_ptr(&data->expands) != 0)
		return (internal_error_return(ERROR_MALLOC));
	data->and_or = 0;
	return (0);
}
