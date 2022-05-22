/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:34:44 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/22 23:10:57 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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
# include <stdbool.h>

# define BLUE "\033[38;5;36m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

# define PROMPT "TheShell"

typedef enum e_error
{
	ALL_FINE,
	ERR_CATCHALL,
	MALLOC_FAIL,
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
	LOG_OR
}	t_type;

typedef struct s_flags
{
	int single_quote;
	int	double_quote;
}	t_flags;

typedef struct s_cmd
{
	char			**cmd_arg;
	char			**paths;
	char			*cmd_path;
	int				in;
	int				out;
	int				pid;
	struct s_cmd	*pipe_prev;
	struct s_cmd	*pipe_next;
}	t_cmd; 

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
	char			**expands;//expands[cmd][dollar] == 1 if that dollar expands, 0 if not
	int				exit_code;
	int				std_in;
	int				std_out;
	int				and_or;
	struct s_data	*next;
}	t_data;

int	lexer(t_data *data);
int	parser(t_data *data);
int	create_cmd_args(t_data *data);
void	save_redirs_in_cmds(t_data *data);
int		do_heredoc(t_data *data);
void	in_out_std(t_data *data);

int	init_data(t_data **data, char **envp, int argc, char **argv);
int	add_char_ptr(char ***arr);
int	add_char(char **str, char c);
int	ft_add_str(char **str, char *add);

/*	utils						*/

int		ft_err(t_error err);
int		ft_syntax_err(char *token);
int		ft_blank_err_near(char *blank, char *token);

int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_strlen(const char *str);
void	ft_putstr_fd(char *str, int fd);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strndup(char *ptr, int len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

char	*ft_strdup(const char *s1);
char	**clone_envp(char **envp);
int		is_meta(char c);
int		ft_strcmp_x(const char *s1, const char *s2, size_t n);

/*	token utils					*/

int		is_end_of_token(t_data *data, char c);
t_token	*create_new_token(void);
t_token	*token_last(t_token *token);
void	token_add_back(t_token **list, t_token *new);
int		check_if_new_cmd(t_data *data);

int		ft_tokenlen(t_data *data, int *i);
void	del_token(t_token **token);
int		is_redir(t_type type);
void	del_next_token(t_token *token);

/*	free						*/

void	free_2d_char(char ***cmds);
void	free_cmds(t_cmd **cmds);
void	free_tokens(t_token **tokens);

//Sig
void    signal_handler(t_data *data);

//Expander
char	*expander(char *input, t_data *data);
char	*ft_substr_append(char const *s, unsigned int start, size_t len, char c);
char	*ft_strionjoin(char *s1, char *s2, int n, int *index);

void    subshells(t_data *data);

#endif