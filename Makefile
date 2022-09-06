# todo: remove -g from CFLAGS
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
SRC = \
	builtin_cd.c \
	builtin_echo.c \
	builtin_env.c \
	builtin_exit.c \
	builtin_export.c\
	builtin_pwd.c \
	builtin_unset.c \
	concatenate.c \
	environ.c \
	error.c \
	expansion_find_end.c \
	expansion_split.c \
	expansion.c \
	get_next_line.c \
	handlers.c \
	heredoc.c \
	history.c \
	main.c \
	minishell.c \
	print_utils.c \
	read_input.c \
	resolve_path.c \
	status.c \
	t_command_utils.c \
	tokenizer.c \

OBJ = $(addprefix $(SRC_DIR)/, $(SRC:.c=.o))

INCLUDE_DIR = include
HEADERS = minishell.h
INCLUDE = $(addprefix $(INCLUDE_DIR)/, $(HEADERS))

.PHONY: all clean fclean re

all: ${NAME}

${NAME}: libft/libft.a ${OBJ}
	@ ${CC} ${CFLAGS} -o ${NAME} ${OBJ} -L libft -lreadline -lft 

%.o: %.c ${INCLUDE}
	@ ${CC} -c ${CFLAGS} -I${INCLUDE_DIR} -o $@ $<

libft/libft.a:
	@ make -C libft

clean:
	@ make -C libft clean
	@ ${RM} ${OBJ}

fclean: clean
	@ make -C libft fclean
	@ ${RM} ${NAME}

re: fclean all

rm_path:
	OLD_PATH=${PATH}
	unset PATH