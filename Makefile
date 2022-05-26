# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 20:10:21 by mmeising          #+#    #+#              #
#    Updated: 2022/05/26 21:34:03 by mmeising         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ./minishell

CC := gcc
CFLAGS ?= -Wall -Werror -Wextra

MAIN_S := 	main.c 						\
			data.c 						\
			free.c 						\
			input.c 					\
			signal.c 					\
			syntax_check.c				\

PARSE_S := 	lexer.c 					\
			lexer_get_type.c			\
			parser.c 					\
			parser_checks.c				\
			heredoc.c					\
			in_out_std.c				\
			expands_utils.c 			\
			create_cmd_args.c 			\
			save_redirs_in_cmds.c		\
			debug.c						\

EXPAN_S	:=	expander.c					\
			wildcards.c					\
			meta.c 						\
			e_utils.c 					\

SUB_S :=	fork.c 						\
			splitter.c 					\
			and_or.c 					\
			pipe.c						\
			pipe_checks.c				\
			subshell.c					\
			utils.c						\
			utils_sep.c 				\


EXEC_S :=	exec.c						\
			forks.c 					\
			path.c 						\

ERROR :=	errors.c					\
			put_error.c					\


BUILT :=	builtins.c					\
			cd.c 						\
			echo.c 						\
			env.c						\
			export.c 					\
			pwd.c 						\
			unset.c 					\
			exit.c 						\

UTILS :=	ft_calloc.c 				\
			ft_strlen.c 				\
			ft_strdup.c 				\
			ft_split.c					\
			ft_splitpath.c 				\
			ft_strjoin.c 				\
			ft_strjoin3.c 				\
			ft_strcmp.c 				\
			ft_strncmp.c 				\
			ft_strchr.c 				\
			ft_stristr.c 				\
			ft_straiojoin.c 			\
			ft_strionjoin.c 			\
			ft_strndup.c 				\
			ft_putstr_fd.c 				\
			ft_strlcpy.c 				\
			ft_strcmp_x.c				\
			token_utils.c				\
			token_utils2.c				\
			is_something.c 				\
			ft_substr.c 				\
			ft_substr_append.c 			\
			ft_find_replace.c 			\
			ft_itoa.c					\

OBJ_DIR := ./_obj

MAIN_O := $(addprefix $(OBJ_DIR)/, $(MAIN_S:.c=.o))
PARSE_O := $(addprefix $(OBJ_DIR)/, $(PARSE_S:.c=.o))
EXPAN_O := $(addprefix $(OBJ_DIR)/, $(EXPAN_S:.c=.o))
SUB_O := $(addprefix $(OBJ_DIR)/, $(SUB_S:.c=.o))
EXEC_O := $(addprefix $(OBJ_DIR)/, $(EXEC_S:.c=.o))
ERROR_O := $(addprefix $(OBJ_DIR)/, $(ERROR:.c=.o))
BUILT_O := $(addprefix $(OBJ_DIR)/, $(BUILT:.c=.o))
UTILS_O := $(addprefix $(OBJ_DIR)/, $(UTILS:.c=.o))

MAIN_S := $(addprefix main/, $(MAIN_S))
PARSE_S := $(addprefix parser/, $(PARSE_S))
EXPAN_S := $(addprefix expander/, $(EXPAN_S))
SUB_S := $(addprefix subshell/, $(SUB_S))
EXEC_S := $(addprefix executer/, $(EXEC_S))
ERROR := $(addprefix errors/, $(ERROR))
BUILT := $(addprefix builtins/, $(BUILT))
UTILS := $(addprefix utils/, $(UTILS))

INC_HEADER := -I ./include
INCLUDES := -lreadline

# Colorcodes
Y := "\033[33m"
R := "\033[31m"
G := "\033[32m"
B := "\033[34m"
X := "\033[0m"
UP := "\033[A"
CUT := "\033[K"

all: $(NAME)

$(NAME): $(MAIN_O) $(PARSE_O) $(EXPAN_O) $(SUB_O) $(EXEC_O) $(ERROR_O) $(BUILT_O) $(UTILS_O)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	$(CC) $(CFLAGS) $(MAIN_O) $(PARSE_O) $(EXPAN_O) $(SUB_O) $(EXEC_O) $(ERROR_O) $(BUILT_O) $(UTILS_O) $(INCLUDES) -o $(NAME)
	@printf $(UP)$(CUT)
	@echo $(G)Finished"  "[$(NAME)]...$(X)

$(OBJ_DIR)/%.o: ./main/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

$(OBJ_DIR)/%.o: ./parser/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

$(OBJ_DIR)/%.o: ./expander/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

$(OBJ_DIR)/%.o: ./subshell/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

$(OBJ_DIR)/%.o: ./executer/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

$(OBJ_DIR)/%.o: ./errors/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

$(OBJ_DIR)/%.o: ./builtins/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

$(OBJ_DIR)/%.o: ./utils/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

clean:
	@if [ -d "${OBJ_DIR}" ]; then \
		echo $(R)Cleaning"  "[$(OBJ_DIR)]...$(X); \
		rm -r ${OBJ_DIR}; \
		echo $(G)Cleaned!$(X); \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo $(R)Cleaning"  "[$(NAME)]...$(X); \
		rm -r $(NAME); \
		echo $(G)Cleaned!$(X); \
	fi

re: fclean all

debug: fclean
	$(CC) $(CFLAGS) -g $(INC_HEADER) $(MAIN_S) $(PARSE_S) $(EXPAN_S) $(SUB_S) $(EXEC_S) $(ERROR) $(BUILT) $(UTILS) $(INCLUDES) -o debug
	lldb debug

.PHONY: all clean fclean re debug