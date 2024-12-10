# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 14:59:57 by eschmitz          #+#    #+#              #
#    Updated: 2024/12/10 16:34:00 by eschmitz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra #-g3 -fsanitize=address
RM		= rm -rf

# Libraries

MINISHELL_DIR	=	./includes/
READLINE_DIR	=	$(HOME)/.brew/opt/readline
READLINE_LIB	=	-L$(READLINE_DIR)/lib -lreadline

# Include directories

INC_DIRS		=	include source /include $(READLINE_DIR)/include $(MINISHELL_DIR)
CFLAGS			+=	$(addprefix -I, $(INC_DIRS))
LDFLAGS			=	$(READLINE_LIB)

# Source files

VPATH	= source source/ast source/built_ins source/checker source/executor \
			source/main source/parsing source/utils source/lexer source/free \
			source/expander

SRC_MAIN	= main.c shell_init.c
SRC_UTILS	= libft_utils.c libft_utils_2.c ft_split.c utils.c libft_utils_3.c
SRC_PARSING	= cmd_parser.c pars.c pipe_parser.c redir_parser.c
SRC_BUILT_INS	= cd.c echo.c env.c export.c export_utils.c path.c pwd.c \
					b_utils.c export_print.c unset.c
SRC_CHECKER	= check.c errors.c
SRC_LEXER	= lexer.c lexer_utils.c trimmer.c verif_lex.c
SRC_EXPANDER	= expander.c env_var.c expand_heredoc.c expand_quotes.c \
					expander_utils.c expander_utils2.c get_word.c
SRC_EXECUTOR	= exec_cmd.c exec.c exec_heredoc.c exec_pipe.c exec_input.c \
					exec_trunc_append.c
SRC_FREE	= free.c free_ast.c

SRC	= $(SRC_MAIN) $(SRC_UTILS) $(SRC_PARSING) $(SRC_BUILT_INS) \
		$(SRC_CHECKER) $(SRC_EXECUTOR) $(SRC_LEXER) $(SRC_FREE) \
		$(SRC_EXPANDER)

# Object files

OBJ		= $(SRC:%.c=objects/%.o)
DEP		= $(OBJ:%.o=%.d)
OBJ_PATH = objects

# Rules

all: $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

objects/%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_PATH) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
	@echo "\033[31m              __          __          __                __ __   "
	@echo "\033[32m             |  \        |  \        |  \              |  \  \  "
	@echo "\033[33m ______ ____  \▓▓_______  \▓▓ _______| ▓▓____   ______ | ▓▓ ▓▓  "
	@echo "\033[34m|      \    \|  \       \|  \/       \ ▓▓    \ /      \| ▓▓ ▓▓  "
	@echo "\033[31m| ▓▓▓▓▓▓\▓▓▓▓\ ▓▓ ▓▓▓▓▓▓▓\ ▓▓  ▓▓▓▓▓▓▓ ▓▓▓▓▓▓▓\  ▓▓▓▓▓▓\ ▓▓ ▓▓  "
	@echo "\033[32m| ▓▓ | ▓▓ | ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓\▓▓    \| ▓▓  | ▓▓ ▓▓    ▓▓ ▓▓ ▓▓  "
	@echo "\033[33m| ▓▓ | ▓▓ | ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓_\▓▓▓▓▓▓\ ▓▓  | ▓▓ ▓▓▓▓▓▓▓▓ ▓▓ ▓▓  "
	@echo "\033[34m| ▓▓ | ▓▓ | ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓       ▓▓ ▓▓  | ▓▓\▓▓     \ ▓▓ ▓▓  "
	@echo "\033[31m \▓▓  \▓▓  \▓▓\▓▓\▓▓   \▓▓\▓▓\▓▓▓▓▓▓▓ \▓▓   \▓▓ \▓▓▓▓▓▓▓\▓▓\▓▓  "
	@echo "\n                                                                      "

clean:
	@$(RM) objects
	@echo "\nYour program got cleaned successfully\n"
	@if [ -f traces.txt ]; then $(RM) traces.txt; fi
	@if [ -f 0 ]; then $(RM) 0; fi

fclean: clean
	@$(RM) $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
