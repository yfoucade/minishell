/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:00:18 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/22 16:27:47 by jallerha         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include "libft.h"

# ifndef STOP_NON_INT
#  define STOP_NON_INT

extern char	g_stop_non_int;

# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef EOL
#  define EOL -2
# endif

# ifndef ERROR
#  define ERROR -1
# endif

# ifndef READING
#  define READING 1
# endif

# define CHILD 0
# define PARENT 1

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE 1

# define PIPE_OUT 0
# define PIPE_IN 1

# define NO_ACCESS 0x0
# define READABLE 0x1
# define WRITEABLE 0x2
# define EXECUTABLE 0x4
# define IS_DIR 0x8
# define EXISTS 0x10

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define COLOR_RESET "\e[0m"

# define CMD_BUILTIN 1
# define CMD_ABS_PATH 2
# define CMD_NOT_FOUND 3

# define ERR_MALLOC 1
# define ERR_QUOTE 2
# define ERR_PIPELINE 3
# define ERR_FILENAME_MISSING 4

# define UC unsigned char

struct		s_status;
struct		s_command;

typedef UC	(*t_builtin_ptr)(struct s_status *);

// todo: change for struct s_program and t_program
typedef struct s_command
{
	union
	{
		t_builtin_ptr	fun_ptr;
		char			*command_path;
	} u_command_ref;
	char	command_type;
}	t_command;

typedef struct s_status
{
	char			*input;
	char			ft_isatty;
	t_str_list		*pipelines;
	t_str_list		*commands;
	t_str_list		*curr_command;
	t_str_list		*tokens;
	t_str_list		*lst_args;
	t_str_list		*lst_redirections;
	char			**args;
	char			**redirections;
	char			**environ;
	int				*in_pipe;
	int				*out_pipe;
	char			*curr_pipeline;
	char			*prev_pipeline;
	t_command		*command;
	unsigned char	return_value;
	char			*error_msg;
	pid_t			child_id;
	int				child_exit_status;
	unsigned char	tmp_exit;
	unsigned char	exit_status;
	int				in_fd;
	int				out_fd;
}	t_status;

typedef struct s_redirection
{
	int						redirection_type;
	char					*filename;
	char					*expanded_filename;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_env_variable
{
	char	*name;
	char	*value;
}	t_env_variable;

typedef struct s_file_buffer
{
	char	buf[BUFFER_SIZE + 1];
	int		current_index;
}	t_file_buffer;

// builtin_cd.c
unsigned char	cd(t_status *status);

// builtin_echo.c
unsigned char	echo(t_status *status);

// builtin_env.c
unsigned char	env(t_status *status);

// builtin_exit.c
unsigned char	ft_exit(t_status *status);

// builtin_export.c
char			add_env_variable(t_status *status, char *name, char *value);
char			is_valid_identifier(char *str); //same
char			replace_or_add(t_status *status, char *name, char *value);
unsigned char	export(t_status *status);

// builtin_pwd.c
unsigned char	pwd(t_status *status);

// builtin_unset.c
unsigned char	unset(t_status *status);

//builtin_utils.c
t_builtin_ptr	search_builtins(char *command);
unsigned char	execute_builtin(t_status *status);

// concatenate.c
int				get_total_size(t_str_list *chunks);
void			fill(char *res, t_str_list *chunks);
char			*concatenate(t_str_list *chunks);

// environ.c
int				array_size(char **array);
char			**copy_environ(char **env);
char			*ft_getenv(t_status *status, char *variable);
char			add_custom_variables(t_status *status);
t_env_variable	*parse_env_variable(char *str);

// error.c
void			panic(t_status *status);
void			malloc_error(t_status *status);
char			set_error_msg(t_status *status, char *str);
void			flush_error_msg(t_status *status, char *str);
int				ft_cmd_not_found(char *command);

// expansion_find_end.c
char			*find_variable_end(char *s);
char			*find_constant_end(char *command);
char			*find_chunk_end(char *command);

// expansion_split.c
char			add_next_chunk(t_str_list **chunks, char **str);
t_str_list		*construct_raw_linked_list(char *str);
t_str_list		*split_three_type(char *str);

// expansion.c
char			*expand(t_status *status, char *command);
char			expand_array_elements(t_status *status, char **array);

// ft_access.c
int				ft_access(char *path);

// get_next_line.c
char			*get_next_line(int fd);
int				get_chunk(int fd, char *chunk_buf);

// handler_installers.c
void			install_handlers(t_status *status, int caller);
void			waiting_handlers(t_status *status);
void			heredoc_handlers(t_status *status);
void			uninstall_handlers(t_status *status);

// handlers.c
void			parent_handler(int sig);
void			waiting_child(int sig);
void			non_interactive_parent_handler(int sig);
void			child_handler(int sig);
void			non_interactive_child_handler(int sig);

// heredoc.c
char			create_heredoc(t_status *status, char *delim);

// history.c
void			decide_add_history(t_status *environ);

// minishell.c
void			run_shell(t_status *environ);

// parse_name.c
char			*parse_name(t_status *status, char *str);

// parse.c
char			parse(t_str_list *tokens, t_str_list **args,
					t_str_list **redirections);
char			parse_status(t_status *status);
char			parse_curr_command(t_status *status);

//pipe.c
void			free_pipe(int **tab);
void			create_pipe(int **tab);
void			close_pipe_end(int *tab, int end);

//pipeline.c
char			is_valid_quoting(char *str);
char			is_valid_pipeline(t_str_list *commands);
void			save_prev_pipeline(t_status *status);
void			free_curr_pipeline(t_status *status);
void			free_pipelines(t_status *status);

// read_input.c
char			read_input(t_status *status);

// redir_postprocess.c
void			postprocess_redirections(t_status *status);

// redir_preprocess.c
void			process_output(t_status *status);
char			redirect_output(t_status *status, char *type, char *pathname);
char			input_from_file(t_status *status, char *path);
char			redir_input(t_status *status, char *type, char *path_or_delim);
char			preprocess_redirections(t_status *status);

// resolve_path.c
t_command		*resolve_path(t_status *status, char	*command);

// status.c
void			init_status(t_status *environ, char **env);
void			free_status(t_status *status);
void			free_parsed_command(t_status *status);
void			set_exit_status(t_status *status);
void			free_and_exit(t_status *status);

// str_list.c
void			free_str_list(t_str_list *str_list);

// substitute.c
char			substitute_one(t_status *status, t_str_list *chunk);
t_str_list		*substitute_all(t_status *status, t_str_list *chunks);

// t_command_utils.c
void			t_command_set_type(t_command **command, char type);
t_command		*new_t_command(void);
char			t_command_set_fun_ptr(
					t_command **command, t_builtin_ptr fun_ptr);
char			t_command_set_path(
					t_command **command, char *path, char free_path);
void			t_command_free(t_command **command);

// tokenizer.c
char			tokenize(t_status *status, char	*command);
void			print_tokens(t_str_list *tokens);

// tokens.c
char			is_operator(char *token);
char			is_word(char *token);
char			is_valid_syntax(t_str_list	*tokens);

#endif