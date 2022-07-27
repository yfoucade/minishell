/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/07/27 21:31:38 by yfoucade         ###   ########.fr       */
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

void	execute_pipeline(t_environ *environ, t_str_list *commands, int in_pipe[2])
{
	int		out_pipe[2];
	pid_t	pid;

	printf("%d: starting execute_pipeline\n", getpid());
	if (!commands)
	{
		printf("%d: exit\n", getpid());
		exit(0);
	}
	if (in_pipe)
	{
		close(in_pipe[1]);
		dup2(in_pipe[0], STDIN_FILENO);
		printf("%d: reading from: %d\n", getpid(), in_pipe[0]);
	}
	if (commands->next)
	{
		printf("%d: creating out_pipe\n", getpid());
		pipe(out_pipe);
		printf("%d: redirecting stdout\n", getpid());
		dup2(out_pipe[1], STDOUT_FILENO);
		printf("%d: writing to: %d\n", getpid(), out_pipe[1]);
	}
	printf("%d: forking\n", getpid());
	fflush(0);
	pid = fork();
	if (pid)
	{
		close(out_pipe[0]);
		printf("%d: executing command ", getpid());
		DEBUG(commands->str);
		system(commands->str);
		printf("%d: done executing\n", getpid());
		close(out_pipe[1]);
		printf("%d: exit\n", getpid());
		exit(0);
	}
	close(out_pipe[1]);
	execute_pipeline(environ, commands->next, out_pipe);
	printf("%d: exit\n", getpid());
	exit(0);
}

unsigned char	execute_command(t_environ *environ)
{
	pid_t		pid;
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
	pid = fork();
	if (!pid)
		execute_pipeline(environ, splitted_command, NULL);
	wait(NULL);
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
