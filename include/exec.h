/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:58:05 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/01 21:24:53 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "main.h"

//Dup
void	dup_and_exec(t_cmd *cmd, char **envp);
void	executer_finish(t_cmd *first_cmd);
int		get_exitstatus(int pid);
int		fork_exit(t_data **data, t_cmd *cmd, int status);

//Path
char	**get_paths(char **envp);
void	free_paths(char ***paths);
char	*find_cmd(t_data *data, char *cmd, char **paths);

//Status
int		is_exec(t_cmd *cmd);
int		is_exception(char *input);
int		exec_access(t_cmd *cmd);
int		check_empty(t_data *data, t_cmd *cmd);

//Pipes
int		create_pipes(t_data *data, t_cmd *cmd);
void	close_sub(t_cmd *cmd);
void	close_main(t_cmd *cmd);

//Builtins
int		is_builtin(char *s);
int		is_valid(char *var);
int		check_builtin_exec(t_data *data, t_cmd *cmd);
int		check_builtin(t_data *data, t_cmd *cmd);
int		builtin_echo(char **cmd, int fd);
int		builtin_pwd(char *pwd, int fd);
int		builtin_cd(char **cmd, t_data *data);
int		builtin_env(char **cmd, int fd);
int		builtin_export(char **cmd, t_data *data);
int		builtin_unset(char **cmd, t_data *data);

//Env
int		replace_env(char *export, char **envp, int index);
int		realloc_env(t_data *data, int new_exports);
int		addto_env(char **cmd, char **envp);
char	**clone_envp(char **envp);

//Bonus
int		check_wildcards(t_data *data, t_cmd *cmd);

#endif
