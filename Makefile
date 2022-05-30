# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 20:10:21 by mmeising          #+#    #+#              #
#    Updated: 2022/05/30 11:21:17 by lkindere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = builtins errors executer expander main parser subshell utils

NAME := ./minishell

CC := gcc
# CFLAGS ?= -Wall -Werror -Wextra

MAIN_S := 	main.c 						\
			data.c 						\
			free.c 						\
			input.c 					\
			signal.c 					\
			syntax.c					\

PARSE_S := 	lexer.c 					\
			lexer_get_type.c			\
			parser.c 					\
			parser_checks.c				\
			heredoc.c					\
			in_out_std.c				\
			expands_utils.c 			\
			cmd_args.c 					\
			redirs.c					\
			debug.c						\

EXPAN_S	:=	expander.c					\
			wildcards.c					\
			wild_flags.c 				\
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
			dup.c 						\
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
			ft_strwstr.c 				\
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

SRC := $(MAIN_S) $(PARSE_S) $(EXPAN_S) $(SUB_S) $(EXEC_S) $(ERROR) $(BUILT) $(UTILS)
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIB := -lreadline -L/Users/lkindere/.brew/opt/readline/lib
INC := -I ./include

# Colorcodes
Y := "\033[33m"
R := "\033[31m"
G := "\033[32m"
B := "\033[34m"
X := "\033[0m"
UP := "\033[A"
CUT := "\033[K"

all: $(NAME)

# only need to link the readline libraries for the executable with $(LIB)
$(NAME): $(OBJ)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	$(CC) $(CFLAGS) $^ $(LIB) -o $(NAME)
	@printf $(UP)$(CUT)
	@echo $(G)Finished"  "[$(NAME)]...$(X)

# only need the header files for the object file compilation
$(OBJ_DIR)/%.o: %.c
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) -MMD -MP -c $< $(INC) -o $@
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
	$(CC) $(CFLAGS) -g $(INC) $(SRC) $(INC) -o debug
	lldb debug

.PHONY: all clean fclean re debug

-include $(OBJ:.o=.d)