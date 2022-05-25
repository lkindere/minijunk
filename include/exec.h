/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:58:05 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/25 19:37:24 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "main.h"

//Exec
void	dup_and_exec(t_cmd *cmd, char **envp);
int		is_exec(t_cmd *cmd);
void	create_pipes(t_cmd *cmd);

//Path
char	**get_paths(char **envp);
void	free_paths(char ***paths);
char	*find_cmd(char *cmd, char **paths, char *pwd);
char	**clone_envp(char **envp);

//Builtins
int		is_valid(char *var);
int		check_builtin_exec(t_data *data, t_cmd *cmd);
int		check_builtin(t_data *data, t_cmd *cmd);
int		builtin_echo(char **cmd, int fd);
int		builtin_pwd(char *pwd, int fd);
int		builtin_cd(char **cmd, t_data *data);
int		builtin_env(char **cmd, int fd);
int		builtin_export(char **cmd, t_data *data);
int		builtin_unset(char **cmd, t_data *data);

//Bonus
int		check_wildcards(t_data *data, t_cmd *cmd);

//Fake commands
void	fake_commands(t_data *data);

#endif
