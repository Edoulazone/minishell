# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 14:59:57 by eschmitz          #+#    #+#              #
#    Updated: 2024/11/04 16:59:21 by eschmitz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -rf

# Libraries

MINISHELL_DIR	=	./includes/minishell.h
LIBFT_DIR		=	lib/libft
LIBFT			=	$(LIBFT_DIR)/libft.a
READLINE_DIR	=	$(HOME)/.brew/opt/readline
READLINE_LIB	=	-L$(READLINE_DIR)/lib -lreadline

# Include directories

CFLAGS			+=	-I$(dir $(MINISHELL_DIR))
INC_DIRS		=	include source $(LIBFT_DIR)/include $(READLINE_DIR)/include $(MINISHELL_DIR)
CFLAGS			+=	$(addprefix -I, $(INC_DIRS))
LDFLAGS			=	-L$(LIBFT_DIR) -lft $(READLINE_LIB)

# Source files

VPATH	= source source/ast source/built_ins source/checker source/executor \
			source/main source/parser source/utils

SRC_MAIN	= main.c shell_init.c
SRC_UTILS	= utils.c
SRC_PARSING	= parsing.c
SRC_AST		= ast.c ast_utils.c
SRC_BUILT_INS	= cd.c echo.c env.c export.c export_utils.c path.c pwd.c \
					b_utils.c export_print.c unset.c
SRC_CHECKER	= check.c errors.c
SRC_EXECUTOR	= exec_cmd.c exec.c

SRC	= $(SRC_MAIN) $(SRC_UTILS) $(SRC_PARSING) $(SRC_AST) $(SRC_BUILT_INS) \
		$(SRC_CHECKER) $(SRC_EXECUTOR)

# Object files

OBJ		= $(SRC:%.c=build/%.o)
DEP		= $(OBJ:%.o=%.d)
OBJ_PATH = build

# Rules

all: $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

build/%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_PATH) $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) -o $@
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
	@$(RM) ./objects
	@echo "\nYour program got cleaned successfully\n"
	@if [ -f traces.txt ]; then $(RM) traces.txt; fi
	@if [ -f 0 ]; then $(RM) 0; fi

fclean: clean
	@$(RM) $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re