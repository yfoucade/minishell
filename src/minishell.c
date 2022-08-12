/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/12 15:44:32 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	subshell(char **command, int *in_pipe, int *out_pipe)
{
	// make redirections
	// resolve file
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

void	execute_pipeline(t_status *status, t_str_list *commands)
{
	int		*in_pipe;
	int		*out_pipe;
	pid_t	pid;
	int		exit_status;
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
			free_str_list(tokens);
			return ;
		}
		// todo: pretect failure of parse()
		parse(tokens, &lst_args, &redirections);
		// todo: function to expand tokens (first in redirections, look for ambiguity)
		// lst_args: convert to char**
		args = lst_to_array(lst_args);
		if (commands->next)
		{
			out_pipe = malloc(sizeof(*out_pipe) * 2);
			pipe(out_pipe);
		}
		pid = fork();
		if (!pid)
			subshell(args, in_pipe, out_pipe);
		waitpid(pid, &exit_status, 0);
		// use macros to interpret status (man waitpid)
		status->exit_status = exit_status;
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

unsigned char	execute_command(t_status *status)
{
	t_str_list	*splitted_command;

	if (!is_valid_quoting(status->curr_command))
	{
		printf("execute_command: quoting error\n");
		return (QUOTE_ERROR);
	}
	splitted_command = ft_split_unquoted_c(status->curr_command, '|');
	if (!is_valid_pipeline(splitted_command))
	{
		puts("execute_command: pipeline error\n");
		// free_splitted_command(splitted_command);
		return (PIPELINE_ERROR);
	}
	execute_pipeline(status, splitted_command);
	return (0);
}

void	run_shell(t_status *status)
{
	t_str_list	*tmp;

	while (TRUE)
	{
		read_input(status);
		tmp = status->pipelines;
		if (!tmp)
			exit(0);
		while (tmp)
		{
			status->curr_command = ft_strdup(tmp->str);
			if (status->curr_command && *status->curr_command)
			{
				decide_add_history(status);
				status->exit_status = execute_command(status);
				save_last_command(status);
			}
			else
				free_curr_command(status);
			tmp = tmp->next;
		}
		free_pipelines(status);
	}
}
