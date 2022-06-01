/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:50:04 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/01 21:24:37 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	valid_start(char *name, char *cmd)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	j = 0;
	if ((!ft_strncmp(name, ".", 1)) && cmd[0] != '.')
		return (0);
	if (cmd[0] != (char)-1 && cmd[0] != name[0])
		return (0);
	if (cmd[ft_strlen(cmd) - 1] != name[ft_strlen(name) - 1]
		&& cmd[ft_strlen(cmd) - 1] != (char)-1)
		return (0);
	while (cmd[++i])
	{
		if (cmd[i] != (char)-1)
			j++;
	}
	if (j > ft_strlen(name))
		return (0);
	return (1);
}

//Fix ./*	not returning anything
//Returns -1 on errors
//Returns 0 on no match
//Returns 1 on match
int	check_match(char *name, char *cmd)
{
	int		i;
	int		last_index;
	char	**input;

	i = -1;
	last_index = 0;
	if (cmd[0] == '.' && cmd[1] == '/')
		i += 2;
	input = ft_split(cmd, (char)-1);
	if (!input)
		return (-1);
	if (!valid_start(name, cmd) && free_2d_char(&input))
		return (0);
	while (input[++i])
	{
		if (ft_strwstr(&name[last_index], input[i], (char)-1) == -1
			&& free_2d_char(&input))
			return (0);
		last_index += ft_strwstr(&name[last_index], input[i], (char)-1);
	}
	return (free_2d_char(&input));
}

//Wildcards will only work below 500 files per dir
char	**get_wildcards(t_data *data, char *cmd)
{
	DIR				*pwd;
	struct dirent	*dir;
	char			**wildcards;
	int				i;

	i = 0;
	pwd = opendir(data->pwd);
	if (!pwd)
		return (NULL);
	wildcards = ft_calloc(sizeof(char *), 500);
	dir = readdir(pwd);
	while (dir)
	{
		if (i >= 499)
			return (wildcards);
		if (check_match(dir->d_name, cmd))
		{
			wildcards[i] = ft_strdup(dir->d_name);
			if (!wildcards[i++] && error_return("Wildcards", NULL, 1, 0))
				return (wildcards);
		}
		dir = readdir(pwd);
	}
	closedir(pwd);
	return (wildcards);
}

//Overwrites old args with new joined args, 
//updates the index so check_wildcards can continue
//++Index in case of no wildcard matches the arg with * should not be` removed
//eg:
// bash-3.2$ ./potatoes*tomatoes
// bash: ./potatoes*tomatoes: No such file or directory
int	add_wildcards(char **wildcards, t_cmd *cmd, int *index)
{
	char	**new_arg;

	if (!wildcards[0])
	{
		free(wildcards);
		(*index)++;
		return (0);
	}
	new_arg = ft_straiojoin(cmd->cmd_arg, wildcards, index);
	free(wildcards);
	if (!new_arg)
		return (-1);
	free(cmd->cmd_arg);
	cmd->cmd_arg = new_arg;
	return (0);
}

//Iterates through the command args and calls the other functions
int	check_wildcards(t_data *data, t_cmd *cmd)
{
	char	**wildcards;
	int		i;

	i = 0;
	if (!cmd->exp)
		return (0);
	hide_wildcards(cmd);
	while (cmd->cmd_arg[i])
	{
		if (ft_strschr(cmd->cmd_arg[i], (char)-1))
		{
			wildcards = get_wildcards(data, cmd->cmd_arg[i]);
			wildcards = sort_wildcards(wildcards);
			if (!wildcards)
				error_return("Wildcards", NULL, 1, 0);
			if (add_wildcards(wildcards, cmd, &i) != 0)
				error_return("Wildcards", NULL, 1, 0);
		}
		else
			i++;
	}
	unhide_wildcards(cmd);
	return (0);
}
