/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/02 16:25:21 by yfoucade         ###   ########.fr       */
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

void	subshell_2(char **command, int *in_pipe, int *out_pipe)
{
	// make redirections
	// resolve file
	// call execve
	if (in_pipe)
		dup2(in_pipe[0], STDIN_FILENO);
	if (out_pipe)
		dup2(out_pipe[1], STDOUT_FILENO);
	execve(*command, command, NULL);
	exit(0);
}

char	is_operator(char *token)
{
	if (!token)
		return (FALSE);
	if (*token == '<' || *token == '>')
		return (TRUE);
	return (FALSE);
}

char	is_word(char *token)
{
	if (!token)
		return (FALSE);
	return (!is_operator(token));
}

// consider receiving a t_str_list** as well, that we set to
// the element causing the error. If return value is 0 (syntax error),
// then the t_str_list** is made to point to the problematic element.
// If return value is 0 and t_str_list** points to NULL, the problematic
// element is the `newline'.
char	is_valid_syntax(t_str_list	*tokens)
{
	while (tokens)
	{
		if (is_operator(tokens->str))
		{
			if (!tokens->next || !is_word(tokens->next->str))
				return (FALSE);
		}
		tokens = tokens->next;
	}
	return (TRUE);
}

char	parse(t_str_list *tokens, t_str_list **args, t_str_list **redirections)
{
	*args = NULL;
	*redirections = NULL;
	while (tokens)
	{
		//todo: check failure after each update
		if (is_word(tokens->str))
			*args = lst_add(args, tokens->str);
		else
		{
			*redirections = lst_add(redirections, tokens->str);
			tokens = tokens->next;
			*redirections = lst_add(redirections, tokens->str);
		}
		tokens = tokens->next;
	}
	return (SUCCESS);
}

void	execute_pipeline(t_environ *environ_, t_str_list *commands)
{
	int		*in_pipe;
	int		*out_pipe;
	pid_t	pid;
	int		status;
	t_str_list	*tokens;
	t_str_list	*lst_args;
	char		**args;
	t_str_list	*redirections;

	in_pipe = NULL;
	out_pipe = NULL;
	while (commands)
	{
		tokens = tokenize(commands->str);
		if (!is_valid_syntax(tokens))
		{
			printf("minishell: syntax error\n");
			free(in_pipe);
			free_splitted_command(tokens);
			return ;
		}
		// todo: pretect failure of parse()
		parse(tokens, &lst_args, &redirections);
		// printf("Args:\n");
		// print_str_list(lst_args);
		// printf("Redirections:\n");
		// print_str_list(redirections);
		// todo: function to expand tokens (first in redirections, look for ambiguity)
		// lst_args: convert to char**
		args = lst_to_array(lst_args);
		// todo: start subshell
		if (commands->next)
		{
			out_pipe = malloc(sizeof(*out_pipe) * 2);
			pipe(out_pipe);
		}
		pid = fork();
		// if (!pid)
		// 	subshell(commands->str, in_pipe, out_pipe);
		if (!pid)
			subshell_2(args, in_pipe, out_pipe);
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

	if (!is_valid_quoting(environ_->curr_command))
	{
		printf("execute_command: quoting error\n");
		return (ERROR);
	}
	splitted_command = ft_split_unquoted_c(environ_->curr_command, '|');
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
