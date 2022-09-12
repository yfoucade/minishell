NAME = libft.a

SRC = \
	count.c \
	free_array.c \
	free_str_list.c \
	ft_is_alnum.c \
	ft_is_alpha.c \
	ft_split.c \
	ft_split_unquoted_c.c \
	ft_startswith.c \
	ft_strcat.c \
	ft_strcat_free.c \
	ft_strchr.c \
	ft_strchr_chr.c \
	ft_strcmp.c \
	ft_strdup.c \
	ft_strlen.c \
	ft_strndup.c \
	is_blank_chr.c \
	is_blank_str.c \
	is_digit.c \
	is_meta.c \
	lst_add.c \
	lst_add_n.c \
	lst_to_array.c \
	print_utils.c \
	trim.c \
	uctoa.c \

OBJ = ${SRC:.c=.o}

.PHONY: all clean fclean re

all: ${NAME}

${NAME}: ${OBJ}
	@ ar rcs ${NAME} ${OBJ}

%.o: %.c libft.h
	@ gcc -c -I. $<

clean:
	@ ${RM} ${OBJ}

fclean: clean
	@ ${RM} ${NAME}

re: fclean all