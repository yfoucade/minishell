/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/07/31 05:36:13 by yfoucade         ###   ########.fr       */
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

void	subshell(char *command, int *in_pipe, int *out_pipe)
{
	if (in_pipe)
		dup2(in_pipe[0], STDIN_FILENO);
	if (out_pipe)
		dup2(out_pipe[1], STDOUT_FILENO);
	// replace with our own preprocessing and a call to execve()
	system(command);
	exit(0);
}

void	execute_pipeline(t_environ *environ_, t_str_list *commands)
{
	int		*in_pipe;
	int		*out_pipe;
	pid_t	pid;
	int		status;

	in_pipe = NULL;
	out_pipe = NULL;
	while (commands)
	{
		if (commands->next)
		{
			out_pipe = malloc(sizeof(*out_pipe) * 2);
			pipe(out_pipe);
		}
		pid = fork();
		if (!pid)
			subshell(commands->str, in_pipe, out_pipe);
		waitpid(pid, &status, 0);
		// use macros to interpret status (man waitpid)
		environ_->exit_status = status;
		if (in_pipe)
		{
			close(in_pipe[0]);
			free(in_pipe);
		}
		if (out_pipe)
		{
			close(out_pipe[1]);
			in_pipe = out_pipe;
		}
		out_pipe = NULL;
		commands = commands->next;
	}
}

char	is_valid_quoting(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			str = ft_strchr(str + 1, *str);
			if (!*str)
				return (FALSE);
		}
		++str;
	}
	return (TRUE);
}

unsigned char	execute_command(t_environ *environ_)
{
	t_str_list	*splitted_command;

	printf("execute_command: received command: ");
	DEBUG(environ_->curr_command);
	if (!is_valid_quoting(environ_->curr_command))
	{
		printf("execute_command: quoting error\n");
		return (ERROR);
	}
	splitted_command = ft_split_unquoted_c(environ_->curr_command, '|');
	print_str_list(splitted_command);
	if (!is_valid_pipeline(splitted_command))
	{
		puts("execute_command: pipeline error\n");
		// free_splitted_command(splitted_command);
		return (ERROR);
	}
	execute_pipeline(environ_, splitted_command);
	return (0);
}

void	run_shell(t_environ *environ_)
{
	t_str_list	*tmp;

	while (TRUE)
	{
		update_environ(environ_);
		environ_->input = readline(PS1);
		// if NULL print error msg
		environ_->pipelines = ft_split_unquoted_c(environ_->input, '\n');
		tmp = environ_->pipelines;
		if (!tmp)
			// exit_minishell(environ_);
			exit(0);
		while (tmp)
		{
			environ_->curr_command = tmp->str;
			if (environ_->curr_command && *environ_->curr_command)
			{
				decide_add_history(environ_);
				environ_->exit_status = execute_command(environ_);
				free(environ_->last_command);
				environ_->last_command = ft_strdup(environ_->curr_command,
					ft_strlen(environ_->curr_command));
				environ_->curr_command = NULL;
			}
			else
				free(environ_->curr_command);
			tmp = tmp->next;
		}
		free_splitted_command(environ_->pipelines);
	}
}
