/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 00:46:13 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/10 17:05:45 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOLVE_PATH_H
# define RESOLVE_PATH_H

# ifndef ENVIRON
#  define ENVIRON
extern char	**environ;
# endif

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1
# define FAILURE 1
# define SUCCESS 0

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define COLOR_RESET "\e[0m"
# define DEBUG_COLOR RED
# define DEBUG_PREFIX ">>>"
# define DEBUG_SUFFIX "<<<"
# define COLOR(color, str) color str COLOR_RESET
# define DEBUG(str) printf(COLOR(DEBUG_COLOR, DEBUG_PREFIX) "%s" COLOR(DEBUG_COLOR, DEBUG_SUFFIX) "\n", str)
# define ERR_DEBUG(str) write(2, str, sizeof(str));

# define CMD_BUILTIN 1
# define CMD_ABS_PATH 2
# define CMD_NOT_FOUND 3

typedef unsigned char (*builtin_ptr)(char **, char **);

unsigned char	builtin_1(char **args, char **redirections);
unsigned char	builtin_2(char **args, char **redirections);

typedef struct s_str_list
{
	char	*str;
	struct s_str_list	*next;
} t_str_list;

typedef struct s_command
{
	union
	{
		builtin_ptr	fun_ptr;
		char		*command_path;
	} u_command_ref;
	char	command_type;
} t_command;

// ft_split.c
int	ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *haystack, char needle);
char	*ft_strcat(char *s1, char *s2);
char	*ft_strcat_free(char *s1, char *s2, char free_s1, char free_s2);
int		ft_strlen(char *str);
char	*ft_strndup(char *str, int n);
char	*ft_strdup(char *str);
void	print_str_list(t_str_list *str_list);
t_str_list	*ft_split(char *str, char c);
void	free_lst(t_str_list *lst);

// t_command_utils.c
t_command	*new_t_command(void);
char	t_command_set_fun_ptr(t_command **command, builtin_ptr fun_ptr);
char	t_command_set_path(t_command **command, char *path, char free_path);
void	t_command_free(t_command **command);

// resolve_path.c
t_command	*resolve_path(char	*command);

#endif