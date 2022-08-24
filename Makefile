# todo: remove -g from CFLAGS
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
SRC = \
	array.c \
	builtin_cd.c \
	builtin_echo.c \
	builtin_env.c \
	builtin_exit.c \
	builtin_export.c\
	builtin_pwd.c \
	builtin_unset.c \
	environ.c \
	error.c \
	expansion.c \
	handlers.c \
	history.c \
	main.c \
	minishell.c \
	print_utils.c \
	read_input.c \
	resolve_path.c \
	status.c \
	str_list.c \
	strutils.c \
	t_command_utils.c \
	tokenizer.c \

OBJ = $(addprefix $(SRC_DIR)/, $(SRC:.c=.o))

INCLUDE_DIR = include
HEADERS = minishell.h
INCLUDE = $(addprefix $(INCLUDE_DIR)/, $(HEADERS))

.PHONY: all clean fclean re

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} -lreadline

%.o: %.c ${INCLUDE}
	${CC} -c ${CFLAGS} -I${INCLUDE_DIR} -o $@ $<

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

rm_path:
	OLD_PATH=${PATH}
	unset PATH