/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:00:18 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/11 19:32:44 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1
# define PS1 "$ "
# define PS2 "> "

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

typedef struct s_str_list
{
	char				*str;
	struct s_str_list	*next;
} t_str_list;

typedef struct s_status
{
	char			*input;
	t_str_list		*pipelines;
	char			*curr_command;
	char			*last_command;
	int				run;
	unsigned char	exit_status;
}	t_status;

typedef struct s_redirection
{
	int						redirection_type;
	char					*filename;
	char					*expanded_filename;
	struct s_redirection	*next;
}	t_redirection;

// environ.c
void	init_status(t_status *environ);
void	free_environ(t_status *environ);

// history.c
void	decide_add_history(t_status *environ);

// minishell.c
void	run_shell(t_status *environ);

// ft_strutils.c
int		ft_strlen(char	*str);
char	is_digit(char c);
char	ft_strchr_chr(char *haystack, char needle);
int		ft_strcmp(char *s1, char *s2);
char	is_blank_chr(char c);
char	is_blank_str(char *str);
char	*ft_strndup(char *str, int n);
char	*ft_strdup(char *str);
char	*trim(char *str);
char	*ft_strchr(char *haystack, char needle);
char	is_meta(char c);
t_str_list	*lst_add(t_str_list **lst, char *str);
t_str_list	*ft_split_unquoted_c(char *str, char c);
char	**lst_to_array(t_str_list *lst);

// tokenizer.c
t_str_list	*tokenize(char	*command);
void	print_tokens(t_str_list *tokens);

// expansion.c
char	*expand(char *command);

// handlers.c
void	install_handlers(void);

// str_list.c
void	free_str_list(t_str_list *str_list);

// print_utils.c
void	print_str_list(t_str_list *str_list);
void	print_str_tab(char **str_tab);

#endif