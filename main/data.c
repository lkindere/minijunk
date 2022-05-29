/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:23:20 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/29 03:49:40 by lkindere         ###   ########.fr       */
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

//Allocates memory for init data
//Exits on error
int	alloc_data(t_data **data, char **envp)
{
	(*data) = ft_calloc(1, sizeof(t_data));
	if (!(*data))
		internal_error_exit(ERROR_MALLOC);
	(*data)->cmds = ft_calloc(1, sizeof(t_cmd));
	if ((*data)->cmds == NULL)
		internal_error_exit(ERROR_MALLOC);
	if (add_char_ptr(&(*data)->expands) != 0)
		internal_error_exit(ERROR_MALLOC);
	(*data)->pwd = getcwd((*data)->pwd, 0);
	if (!(*data)->pwd)
		internal_error_exit(ERROR_MALLOC);
	(*data)->envp = clone_envp(envp);
	return (0);
}

/*
 *	Initializes data.
 */
int	init_data(t_data **data, char **envp)
{
	alloc_data(data, envp);
	// (*data)->std_in = dup(STDIN_FILENO);
	// (*data)->std_out = dup(STDOUT_FILENO);
	(*data)->cmds->in = -2;
	(*data)->cmds->out = -2;
	(*data)->pipe1[0] = -1;
	(*data)->pipe1[1] = -1;
	(*data)->pipe2[0] = -1;
	(*data)->pipe2[1] = -1;
	(*data)->is_fork = 0;
	(*data)->and_or = 0;
	return (0);
}

/*
 *	Resets all members of the data struct not reused for the next input.
 */
void	reset_mem(t_data *data)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->cmds)
		free_cmds(&data->cmds);
	if (data->tokens)
		free_tokens(&data->tokens);
	if (data->expands)
		free_2d_char(&data->expands);
}

/*
 *	Resets the data that needs to be cleaned for every time we get new input.
 *	Includes resetting stdin and stdout from the backup saved in data.
 */
int	reset_data(t_data *data)
{
	reset_mem(data);
	data->flags.single_quote = 0;
	data->flags.double_quote = 0;
	data->cmd_count = 0;
	data->dollar_count = 0;
	data->and_or = 0;
	data->cmds = ft_calloc(1, sizeof(t_cmd));
	if (data->cmds == NULL)
		internal_error_exit(ERROR_MALLOC);
	data->cmds->in = -2;
	data->cmds->out = -2;
	if (add_char_ptr(&data->expands) != 0)
		return (internal_error_return(ERROR_MALLOC));
	return (0);
}
