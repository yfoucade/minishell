/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:00:18 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/17 10:20:02 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef ENVIRON
#  define ENVIRON
extern char	**environ;
# endif

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
# include <dirent.h>

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE 1
# define ERROR 1
# define PS1 "$ "
# define PS2 "> "

# define PIPE_OUT 0
# define PIPE_IN 1

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

# define QUOTE_ERROR 1
# define PIPELINE_ERROR 2

# define CMD_BUILTIN 1
# define CMD_ABS_PATH 2
# define CMD_NOT_FOUND 3

# define IGNORE_AMBIGUOUS 0
# define ERROR_ON_AMBIGUOUS 1

typedef unsigned char (*builtin_ptr)(char **, char **);

typedef struct s_str_list
{
	char				*str;
	struct s_str_list	*next;
} t_str_list;

// todo: change for struct s_program and t_program
typedef struct s_command
{
	union
	{
		builtin_ptr	fun_ptr;
		char		*command_path;
	} u_command_ref;
	char	command_type;
} t_command;

typedef struct s_status
{
	char				*input;
	t_str_list			*pipelines;
	int					*in_pipe;
	int					*out_pipe;
	char				*curr_command; // change to curr_pipeline
	char				*last_command; // last_pipeline
	struct s_command	*command;
	int					run;
	pid_t				child_id;
	unsigned char		exit_status;
}	t_status;

typedef struct s_redirection
{
	int						redirection_type;
	char					*filename;
	char					*expanded_filename;
	struct s_redirection	*next;
}	t_redirection;

// status.c
void	init_status(t_status *environ);
void	free_status(t_status *status);
void	save_last_command(t_status *status);
void	free_curr_command(t_status *status);
void	free_pipelines(t_status *status);
void	free_pipe(int **tab);
void	create_pipe(int **tab);
void	close_pipe_end(int *tab, int end);

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
char	*ft_strcat(char *s1, char *s2);
char	*ft_strcat_free(char *s1, char *s2, char free_s1, char free_s2);
t_str_list	*ft_split(char *str, char c);

// tokenizer.c
t_str_list	*tokenize(char	*command);
void	print_tokens(t_str_list *tokens);

// expansion.c
char	*expand(char *command);
char	expand_array_elements(char **array);

// handlers.c
void	install_handlers(void);

// read_input.c
char	read_input(t_status *status);

// resolve_path.c
t_command	*resolve_path(char	*command);

// str_list.c
void	free_str_list(t_str_list *str_list);

// t_command_utils.c
void	t_command_set_type(t_command **command, char type);
t_command	*new_t_command(void);
char	t_command_set_fun_ptr(t_command **command, builtin_ptr fun_ptr);
char	t_command_set_path(t_command **command, char *path, char free_path);
void	t_command_free(t_command **command);

// print_utils.c
void	print_str_list(t_str_list *str_list);
void	print_str_tab(char **str_tab);

#endif