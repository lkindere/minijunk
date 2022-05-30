/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:26:03 by lkindere          #+#    #+#             */
/*   Updated: 2022/05/30 20:09:10 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Will contain universal includes/defines
//And utils that are usable in all parts of the code

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <dirent.h>
# include <stdbool.h>
# include <stdint.h>

# define SHELLNAME	"MiniJunk"
# define PROMPT "MiniJunk"

# define BLUE "\033[38;5;36m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

typedef enum e_type
{
	NONE,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	PIPE,
	WORD,
	END,
	PAR_OPEN,
	PAR_CLOSE,
	LOG_AND,
	LOG_OR,
	AMPERSAND
}	t_type;

typedef struct s_flags
{
	int	single_quote;
	int	double_quote;
}	t_flags;

typedef struct s_token
{
	t_type			type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char			*input;
	struct s_cmd	*cmds;
	char			**envp;
	char			*pwd;
	t_token			*tokens;
	t_flags			flags;
	int				cmd_count;
	int				dollar_count;
	char			**expands;
	int				exit_code;
	// int				std_in;
	// int				std_out;
	int				is_fork;
	int				and_or;
	int				pipe1[2];
	int				pipe2[2];
}	t_data;

typedef struct s_cmd
{
	char			**cmd_arg;
	char			**paths;
	char			*cmd_path;
	int				in;
	int				out;
	int				pid;
	char			*exp;
	struct s_cmd	*pipe_prev;
	struct s_cmd	*pipe_next;
}	t_cmd;

typedef enum e_error
{
	ERROR_NULL,
	ERROR_WRITE,
	ERROR_EXEC,
	ERROR_DUP,
	ERROR_CLOSE,
	ERROR_PIPE,
	ERROR_FORK,
	ERROR_MALLOC,
	ERROR_NO_PATHS,
	ERROR_NO_CMD,
	ERROR_NO_CMD_EXEC_PERMISSION
}	t_error;

//Main
int		syntax_check(t_data *data, char **full_input);
int		the_loop(char **input, char **segment, t_data *data);
int		lexer(t_data *data);
int		parser(t_data *data);
char	*expander(char *input, t_data *data, int heredoc);
void	executer(t_data *data, t_cmd *cmd);

//Data
int		init_data(t_data **data, char **envp);
int		terminator(t_data **rip);
int		reset_data(t_data *data);
void	reset_mem(t_data *data);

int		add_char_ptr(char ***arr);
int		add_char(char **str, char c);
int		ft_add_str(char **str, char *add);

//Env
char	**clone_envp(char **envp);
int		is_set(char *var, char **envp);

//Input
void	get_input(char **full_input, t_data *data);
int		input_is_empty(char	*input);
int		is_input(char *full_input, char *segment);

//Signal
int		signal_default(void);
void	signal_handler(void);
void    signal_unhandler(void);

//Exit
int		exit_code(int new);
int		get_exitstatus(int pid);
int		builtin_exit(t_cmd *cmd, t_data *data);

/*----------ERRORS----------*/
//Exec
int		put_error(char *a, char *b, char *c, char *d);
int		error_exit(char *cmd, char *arg, int error, int exitcode);
int		error_return(char *cmd, char *arg, int error, int exitcode);
int		internal_error_return(t_error error);
void	internal_error_exit(t_error error);
int		blank_err(t_data *data, char *blank, char *token);

/*----------UTILS----------*/
//String compare
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strcmp_x(const char *s1, const char *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strschr(const char *s, int c);
int		ft_strwstr(const char *haystack, const char *needle, int w);
//String manipulation
char	*ft_strdup(const char *s1);
char	*ft_strndup(char *ptr, int len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	*ft_strionjoin(char *s1, char *s2, int n, int *index);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_substr_append(char *s, unsigned int start, size_t len, char c);
void	ft_find_replace(char *str, int c, int r, int d);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
//Array
char	**ft_split(char const *s, char c);
char	**ft_splitpath(char const *s, char c);
char	**ft_straiojoin(char **a1, char **a2, int *index);
//Memory
void	*ft_calloc(size_t count, size_t size);
void	free_cmds(t_cmd **cmds);
void	free_tokens(t_token **tokens);
int		free_2d_char(char ***cmds);
//Checks
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
//Output
void	ft_putstr_fd(char *str, int fd);
char	*ft_itoa(int n);
//Misc
int		is_meta(char c);

void   rl_replace_line (const char *text, int clear_undo);

#endif