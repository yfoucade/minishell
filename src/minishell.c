/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/07/15 00:00:10 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	execute_command(t_environ *environ)
{
	t_str_list	*splitted_command;

	printf("execute_command: received command: ");
	DEBUG(environ->curr_command);
	splitted_command = ft_split_unquoted_c(environ->curr_command, '|');
	print_str_list(splitted_command);
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
