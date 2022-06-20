# todo: remove -g from CFLAGS
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
SRC = minishell.c environ.c
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