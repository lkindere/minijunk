# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 20:10:21 by mmeising          #+#    #+#              #
#    Updated: 2022/05/25 19:27:02 by lkindere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ./minishell

CC := gcc
CFLAGS ?= -Wall -Werror -Wextra

M_SRC := 	main.c 						\
			data.c 						\
			input.c 					\
			signal.c 					\

P_SRC := 	lexer.c 					\
			free.c 						\
			expands_utils.c 			\
			parser.c 					\
			create_cmd_args.c 			\
			save_redirs_in_cmds.c		\
			heredoc.c					\
			in_out_std.c				\
			expander.c 					\

S_SRC :=	fork.c 						\
			splitter.c 					\
			and_or.c 					\
			pipe.c						\
			pipe_checks.c				\
			subshell.c					\
			utils.c						\
			utils_sep.c 				\


X_SRC :=	exec.c						\
			forks.c 					\
			path.c 						\
			wildcards.c					\

ERRORS :=	errors.c					\
			err.c						\


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

OBJ_DIR := ./_obj

M_OBJ := $(addprefix $(OBJ_DIR)/, $(M_SRC:.c=.o))
P_OBJ := $(addprefix $(OBJ_DIR)/, $(P_SRC:.c=.o))
S_OBJ := $(addprefix $(OBJ_DIR)/, $(S_SRC:.c=.o))
X_OBJ := $(addprefix $(OBJ_DIR)/, $(X_SRC:.c=.o))
E_OBJ := $(addprefix $(OBJ_DIR)/, $(ERRORS:.c=.o))
B_OBJ := $(addprefix $(OBJ_DIR)/, $(BUILT:.c=.o))
U_OBJ := $(addprefix $(OBJ_DIR)/, $(UTILS:.c=.o))

M_SRC := $(addprefix main/, $(M_SRC))
P_SRC := $(addprefix parser/, $(P_SRC))
S_SRC := $(addprefix subshell/, $(S_SRC))
X_SRC := $(addprefix exec/, $(X_SRC))
ERRORS := $(addprefix errors/, $(E_SRC))
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

$(NAME): $(M_OBJ) $(P_OBJ) $(S_OBJ) $(X_OBJ) $(E_OBJ) $(B_OBJ) $(U_OBJ)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	$(CC) $(CFLAGS) $(M_OBJ) $(P_OBJ) $(S_OBJ) $(X_OBJ) $(E_OBJ) $(B_OBJ) $(U_OBJ) $(INCLUDES) -o $(NAME)
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

$(OBJ_DIR)/%.o: ./subshell/%.c $(HEADERFILES)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) $(INC_HEADER) -c $< -o $@
	@printf $(UP)$(CUT)

$(OBJ_DIR)/%.o: ./exec/%.c $(HEADERFILES)
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
	$(CC) $(CFLAGS) -g $(INC_HEADER) $(M_SRC) $(P_SRC) $(S_SRC) $(X_SRC) $(ERRORS) $(BUILT) $(UTILS) $(INCLUDES) -o debug
	lldb debug

.PHONY: all clean fclean re debug