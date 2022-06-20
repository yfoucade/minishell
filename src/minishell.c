/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/20 22:22:09 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	g_continue;

unsigned char	execute_command(t_environ *environ)
{
	(void)environ;
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	decide_add_history(t_environ *environ)
{
	if (!environ->curr_command)
		return ;
	if (!(environ->last_command))
	{
		add_history(environ->curr_command);
		return ;
	}
	if (ft_strcmp(environ->last_command, environ->curr_command))
		add_history(environ->curr_command);
}

int	run_shell(t_environ *environ)
{
	g_continue = 1;
	while (g_continue)
	{
		update_environ(environ);
		environ->curr_command = readline(PS1);
		if (*environ->curr_command)
		{
			decide_add_history(environ);
			environ->exit_status = execute_command(environ);
			free(environ->last_command);
			environ->last_command = environ->curr_command;
		}
	}
	return (0);
}
