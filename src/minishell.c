/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/21 14:48:58 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	g_continue;

char	*ft_strdup(char *str, int n)
{
	char	*res;
	int		i;
	
	res = malloc(n + 1);
	i = -1;
	while (++i < n + 1)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

char	*trim(char *str)
{
	char	*res;
	char	*start;
	char	*end;

	start = str;
	while (*start && is_blank_chr(*start))
		start++;
	end = start;
	res = start - 1;
	while (*++res)
	{
		if (!is_blank_chr(*res))
			end = res;
	}
	res = ft_strdup(start, end - start);
	return (res);
}

unsigned char	execute_command(t_environ *environ)
{
	char		*command;
	// t_token		*tokens;

	printf("execute_command: received command: |%s|\n", environ->curr_command);
	command = trim(environ->curr_command);
	printf("execute_command: trimmed command: |%s|\n", command);
	// if (!command)
	// 	exit_minishell(environ);
	// tokens = tokenize(command);
	return (0);
}

void	run_shell(t_environ *environ)
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
}
