CC		= cc
CFLAGS	= -Wall -Werror -Wextra
NAME	= minishell

SRC_PATH = source/lexer source/parser source/main source/utils
OBJ_PATH = objects/

SRC		= main.c commands.c parsing.c auto_complete.c utils.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

OBJ		= $(SRC:.c=.o)

OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INCS	= -I ./../includes/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(NAME): $(OBJ_PATH) $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
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
	@rm -rf $(OBJ_PATH)
	@echo "\nYour program got cleaned successfully\n"
	@if [ -f traces.txt ]; then rm -rf traces.txt; fi
	@if [ -f 0 ]; then rm -rf 0; fi

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re