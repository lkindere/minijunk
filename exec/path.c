/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:46:34 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/22 17:48:58 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Command not found should return 127 exit code
//Checks if command exists in paths
char	*find_cmd(char *cmd, char **paths, char *pwd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin(paths[i++], cmd);
		if (!full_path)
			internal_error_exit(ERROR_MALLOC);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
	}
	if (!paths || !paths[i])
	{
		full_path = ft_strjoin3(pwd, "/", cmd);
		if (!full_path)
			internal_error_exit(ERROR_MALLOC);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		error_exit(cmd, "command not found", 0, 127);
	}
	return (NULL);
}

//Grabs path from environment and splits it into **char appending / to each path
char	**get_paths(char **envp, char *cmd)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp && envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp || !envp[i])
		return (NULL);
	paths = ft_splitpath(&envp[i][5], ':');
	if (!paths)
		internal_error_exit(ERROR_MALLOC);
	return (paths);
}

//Takes address of the paths and frees everything setting it to NULL
void	free_paths(char ***paths)
{
	int	i;

	i = 0;
	while (*paths && (*paths)[i])
	{
		free((*paths)[i]);
		(*paths)[i++] = NULL;
	}
	if (*paths)
	{
		free(*paths);
		*paths = NULL;
	}
}

// Clones the starting envp into data
char	**clone_envp(char **envp)
{
	char	**envp_clone;
	int		i;

	i = 0;
	if (!envp)
		internal_error_exit(ERROR_NULL);
	while (envp[i])
		i++;
	envp_clone = malloc(sizeof(char *) * (i + 1));
	if (!envp_clone)
		internal_error_exit(ERROR_MALLOC);
	envp_clone[i] = NULL;
	i = 0;
	while (envp[i])
	{
		envp_clone[i] = ft_strdup(envp[i]);
		if (!envp_clone[i])
			internal_error_exit(ERROR_MALLOC);
		i++;
	}
	return (envp_clone);
}
