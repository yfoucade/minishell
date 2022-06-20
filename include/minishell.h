/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:00:18 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/20 13:28:30 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PS1 "$ "
# define PS2 "> "

typedef struct s_environ
{
	char			*path;
	char			*curr_command;
	char			*last_command;
	unsigned char	exit_status;
}	t_environ;

// environ.c
void	init_environ(t_environ *environ);
void	update_environ(t_environ *environ);
void	free_environ(t_environ *environ);

#endif