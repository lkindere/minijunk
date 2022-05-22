# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 20:10:21 by mmeising          #+#    #+#              #
#    Updated: 2022/05/23 00:28:24 by lkindere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ./minishell

CC := gcc
# CFLAGS ?= -Wall -Werror -Wextra

P_SRC := 	main.c 						\
			err.c 						\
			inits.c 					\
			lexer.c 					\
			free.c 						\
			expands_utils.c 			\
			parser.c 					\
			create_cmd_args.c 			\
			save_redirs_in_cmds.c		\
			heredoc.c					\
			in_out_std.c				\
			signal.c 					\
			subshell.c					\


E_SRC :=	exec.c						\
			forks.c 					\
			path.c 						\
			errors.c 					\
			wildcards.c					\

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

OBJ_DIR := ./obj

P_OBJ := $(addprefix $(OBJ_DIR)/, $(P_SRC:.c=.o))
E_OBJ := $(addprefix $(OBJ_DIR)/, $(E_SRC:.c=.o))
B_OBJ := $(addprefix $(OBJ_DIR)/, $(BUILT:.c=.o))
U_OBJ := $(addprefix $(OBJ_DIR)/, $(UTILS:.c=.o))

P_SRC := $(addprefix parser/, $(P_SRC))
E_SRC := $(addprefix exec/, $(E_SRC))
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

$(NAME): $(P_OBJ) $(E_OBJ) $(B_OBJ) $(U_OBJ)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	$(CC) $(CFLAGS) $(P_OBJ) $(E_OBJ) $(B_OBJ) $(U_OBJ) $(INCLUDES) -o $(NAME)
	@printf $(UP)$(CUT)
	@echo $(G)Finished"  "[$(NAME)]...$(X)

$(OBJ_DIR)/%.o: ./parser/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

$(OBJ_DIR)/%.o: ./exec/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

$(OBJ_DIR)/%.o: ./builtins/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

$(OBJ_DIR)/%.o: ./utils/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p obj
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
	$(CC) $(CFLAGS) -g $(INC_HEADER) $(BUILT) $(E_SRC) $(P_SRC) $(UTILS) $(INCLUDES) -o debug
	lldb debug

.PHONY: all clean fclean re debug