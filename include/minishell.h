/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:00:18 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/21 17:31:56 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0
# define PS1 "$ "
# define PS2 "> "

typedef struct s_environ
{
	char			*path;
	char			*curr_command;
	char			*last_command;
	unsigned char	exit_status;
}	t_environ;

typedef struct s_token
{
	char			*token;
	struct s_token	*next;
} t_token;

// environ.c
void	init_environ(t_environ *environ);
void	update_environ(t_environ *environ);
void	free_environ(t_environ *environ);

// history.c
void	decide_add_history(t_environ *environ);

// minishell.c
void	run_shell(t_environ *environ);

// ft_strutils.c
int		ft_strcmp(char *s1, char *s2);
char	is_blank_chr(char c);
char	is_blank_str(char *str);
char	*ft_strdup(char *str, int n);
char	*trim(char *str);
char	*ft_strchr(char *haystack, char needle);

#endif