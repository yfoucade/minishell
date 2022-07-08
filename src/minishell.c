/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/07/08 11:41:48 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	g_continue;
char	g_readline;

unsigned char	execute_command(t_environ *environ)
{
	char		*command;
	char		*expanded_command;
	t_token		*tokens;
	// t_token		*expanded_tokens;

	printf("execute_command: received command: |%s|\n", environ->curr_command);
	command = trim(environ->curr_command);
	printf("execute_command: trimmed command: |%s|\n", command);
	// if (!command)
	// 	exit_minishell(environ);
	expanded_command = expand(command);
	printf("execute_command: expand command: |%s|\n", expanded_command);
	tokens = tokenize(expanded_command);
	print_tokens(tokens);
	free(command);
	free(expanded_command);
	// free_tokens(tokens);
	return (0);
}

void	run_shell(t_environ *environ)
{
	g_continue = 1;
	while (g_continue)
	{
		update_environ(environ);
		g_readline = 1;
		environ->curr_command = readline(PS1);
		if (environ->curr_command && *environ->curr_command)
		{
			decide_add_history(environ);
			environ->exit_status = execute_command(environ);
			free(environ->last_command);
			environ->last_command = environ->curr_command;
			environ->curr_command = NULL;
		}
		else if (!environ->curr_command)
		{
			// exit_minishell(environ);
			exit(0);
		}
	}
}
