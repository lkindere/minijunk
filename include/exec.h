/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:58:05 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/22 17:48:11 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <dirent.h>

# include "parser.h"

# define SHELLNAME	"TheShell"

// typedef struct s_cmd
// {
// 	char			**cmd_arg;
// 	char			**paths;
// 	char			*cmd_path;
// 	int				in;
// 	int				out;
// 	int				pid;
// 	struct s_cmd	*pipe_prev;
// 	struct s_cmd	*pipe_next;
// }	t_cmd;

// typedef struct s_data
// {
// 	struct s_cmd	**cmds;
// 	char			**envp;
// 	char			*pwd;
// 	int				exit_code;
// }	t_data;

// typedef enum e_error
// {
// 	ERROR_NULL,
// 	ERROR_WRITE,
// 	ERROR_EXEC,
// 	ERROR_DUP,
// 	ERROR_CLOSE,
// 	ERROR_PIPE,
// 	ERROR_FORK,
// 	ERROR_MALLOC,
// 	ERROR_NO_PATHS,
// 	ERROR_NO_CMD,
// 	ERROR_NO_CMD_EXEC_PERMISSION
// }	t_error;

//Exec
void	executer(t_data *data, t_cmd *cmd);
void	dup_and_exec(t_cmd *cmd, char **envp);
int		is_exec(t_cmd *cmd);
void	create_pipes(t_cmd *cmd);
int		get_exitstatus(t_cmd *cmd);

//Path
char	**get_paths(char **envp, char *cmd);
void	free_paths(char ***paths);
char	*find_cmd(char *cmd, char **paths, char *pwd);
char	**clone_envp(char **envp);

//Builtins
int		is_valid(char *var);
int		is_set(char *var, char **envp);
int		check_builtin_exec(t_data *data, t_cmd *cmd);
int		check_builtin(t_data *data, t_cmd *cmd);
int		builtin_echo(char **cmd, int fd);
int		builtin_pwd(char *pwd, int fd);
int		builtin_cd(char **cmd, t_data *data);
int		builtin_env(char **cmd, int fd);
int		builtin_export(char **cmd, t_data *data);
int		builtin_unset(char **cmd, t_data *data);
int     builtin_exit(t_cmd *cmd, t_data *data);

//Errors
void	put_error(char *a, char *b, char *c, char *d);
int		error_exit(char *cmd, char *arg, int error, int exitcode);
int		error_return(char *cmd, char *arg, int error, int exitcode);
int		internal_error_return(t_error error);
void	internal_error_exit(t_error error);

//Bonus
int		check_wildcards(t_data *data, t_cmd *cmd);

//Utils
char	**ft_split(char const *s, char c);
char	**ft_splitpath(char const *s, char c);
char	*ft_strchr(const char *s, int c);
// size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
int		ft_stristr(const char *haystack, const char *needle);
char	**ft_straiofjoin(char **a1, char **a2, int *index);
int		ft_isalpha(int c);
int		ft_isalnum(int c);

//Fake commands
void	fake_commands(t_data *data);

#endif
