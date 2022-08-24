/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/23 23:42:19 by yfoucade         ###   ########.fr       */
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

void	subshell(t_status *status)
{
	// make redirections
	// resolve file
	if (status->in_pipe)
		dup2(status->in_pipe[0], STDIN_FILENO);
	if (status->out_pipe)
		dup2(status->out_pipe[1], STDOUT_FILENO);
	execve(status->command->u_command_ref.command_path, status->args, status->environ);
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

char	parse_status(t_status *status)
{
	t_str_list	*tokens_copy;

	tokens_copy = status->tokens;
	while (tokens_copy)
	{
		//todo: check failure after each update
		if (is_word(tokens_copy->str))
			status->lst_args = lst_add(&status->lst_args, tokens_copy->str);
		else
		{
			status->lst_redirections = lst_add(&status->lst_redirections, tokens_copy->str);
			tokens_copy = tokens_copy->next;
			status->lst_redirections = lst_add(&status->lst_redirections, tokens_copy->str);
		}
		tokens_copy = tokens_copy->next;
	}
	status->args = lst_to_array(status->lst_args);
	status->redirections = lst_to_array(status->lst_redirections);
	return (SUCCESS);
}


unsigned char	parse_curr_command(t_status *status)
{
	status->tokens = tokenize(status->curr_command->str);
	if (!is_valid_syntax(status->tokens))
	{
		set_error_msg(status, "minishell: missing file name\n");
		status->return_value = ERR_FILENAME_MISSING;
		free_str_list(status->tokens);
		status->tokens = NULL;
	}
	parse_status(status);
	if (expand_array_elements(status, status->args))
	{
		printf("minishell: bad substitution\n");
		return (0);
	}
	if (expand_array_elements(status, status->redirections))
	{
		printf("minishell: ambiguous redirect\n");
		return (0);
	}
	status->command = resolve_path(status->args[0]);
	return (SUCCESS);
}

void	execute_builtin(t_status *status)
{
	// first process redirections.
	status->command->u_command_ref.fun_ptr(status);
}

void	execute_commands(t_status *status)
{
	status->curr_command = status->commands;
	while (status->curr_command)
	{
		if (parse_curr_command(status))
			return ;
		if (status->curr_command->next)
			create_pipe(&status->out_pipe);
		if (status->command->command_type == CMD_BUILTIN)
			execute_builtin(status);
		else
		{
			status->child_id = fork();
			if (!status->child_id)
				subshell(status);
			waitpid(status->child_id, &status->exit_status, 0);
		}
		// use macros to interpret status (man waitpid)
		if (status->in_pipe)
		{
			close_pipe_end(status->in_pipe, PIPE_OUT);
			free_pipe(&status->in_pipe);
		}
		if (status->out_pipe)
		{
			close_pipe_end(status->out_pipe, PIPE_IN);
			status->in_pipe = status->out_pipe;
		}
		status->out_pipe = NULL;
		status->curr_command = status->curr_command->next;
		free_parsed_command(status);
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

void	execute_pipeline(t_status *status)
{
	if (!is_valid_quoting(status->curr_pipeline))
	{
		set_error_msg(status, "minishell: quoting error\n");
		status->return_value = ERR_QUOTE;
		status->exit_status = 1;
		return ;
	}
	status->commands = ft_split_unquoted_c(status->curr_pipeline, '|');
	if (!status->commands)
		malloc_error(status);
	else if(!is_valid_pipeline(status->commands))
	{
		set_error_msg(status, "minishell: pipeline error\n");
		status->return_value = ERR_PIPELINE;
	}
	execute_commands(status);
	free_str_list(status->commands);
	status->commands = NULL;
	return ;
}

void	run_shell(t_status *status)
{
	t_str_list	*tmp;

	while (TRUE)
	{
		read_input(status);
		tmp = status->pipelines;
		while (tmp)
		{
			status->curr_pipeline = ft_strdup(tmp->str);
			if (!status->curr_pipeline)
				malloc_error(status);
			if (*status->curr_pipeline)
			{
				decide_add_history(status);
				execute_pipeline(status);
				if (status->return_value)
					flush_error_msg(status);
				save_prev_pipeline(status);
			}
			free_curr_pipeline(status);
			tmp = tmp->next;
		}
		free_pipelines(status);
	}
}
