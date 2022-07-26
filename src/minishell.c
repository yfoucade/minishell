/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/07/18 02:43:10 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_splitted_command(t_str_list *commands)
{
	t_str_list *tmp;

	while (commands)
	{
		tmp = commands->next;
		free(commands->str);
		free(commands);
		commands = tmp;
	}
}

char	is_valid_pipeline(t_str_list *commands)
{
	char	*tmp;

	if (!commands)
		return (FALSE);
	while (commands)
	{
		tmp = commands->str;
		while (*tmp == ' ' || *tmp == '\t')
			tmp++;
		if (!*tmp)
			return (FALSE);
		commands = commands->next;
	}
	puts("is_valid_pipeline: returning true\n");
	return (TRUE);
}

unsigned char	execute_command(t_environ *environ)
{
	t_str_list	*splitted_command;

	printf("execute_command: received command: ");
	DEBUG(environ->curr_command);
	splitted_command = ft_split_unquoted_c(environ->curr_command, '|');
	print_str_list(splitted_command);
	if (!is_valid_pipeline(splitted_command))
	{
		puts("execute_command: pipeline error\n");
		// free_splitted_command(splitted_command);
		return (ERROR);
	}
	return (0);
}

void	run_shell(t_environ *environ)
{
	while (TRUE)
	{
		update_environ(environ);
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
		else
			free(environ->curr_command);
	}
}
