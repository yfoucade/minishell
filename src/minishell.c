/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/22 20:38:37 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	g_continue;

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("token %d: |%s|\n", i++, tokens->token);
		tokens = tokens->next;
	}
}

char	is_meta_except_dollar(char *c)
{
	if (*c == ' ' || *c == '\t')
		return (TRUE);
	if (*c == '<' || *c == '|' || *c == '>')
		return (TRUE);
	if (*c == '\'' || *c == '"') // need to know if it is closed
		if (*ft_strchr(c + 1, *c) == *c)
			return (TRUE);
	return (FALSE);
}

char	*find_token_end(char *command)
{
	char	*closing_quote;

	if (is_blank_chr(*command))
		return (command + 1);
	if (*command == '<' || *command == '>')
		return (command + (command[1] == *command) + 1);
	if (*command == '|')
		return (command + (command[1] == *command) + 1);
	if (*command == '\'' || *command == '"')
	{
		closing_quote = ft_strchr(command + 1, *command);
		if (*closing_quote == *command)
			return (closing_quote + 1);
	}
	while (*command && !is_meta_except_dollar(command))
		command++;
	return (command);
}

void	add_next_token(t_token **tokens, char **command)
{
	char	*end;
	t_token	*tmp;
	t_token	*new_token;

	while (is_blank_chr(**command))
		(*command)++;
	end = find_token_end(*command);
	new_token = malloc(sizeof(new_token));
	new_token->next = NULL;
	// end is the first character that doesn't belong to the token
	new_token->token = ft_strdup(*command, end - *command);
	*command = end;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

t_token	*tokenize(char	*command)
{
	t_token	*res;

	res = (t_token*)malloc(sizeof(res));
	res = NULL;
	while (*command)
	{
		add_next_token(&res, &command);
		// printf("tokenize: token added, remaining: |%s|\n", command);
	}
	return (res);
}

unsigned char	execute_command(t_environ *environ)
{
	char		*command;
	t_token		*tokens;
	// t_token		*expanded_tokens;

	printf("execute_command: received command: |%s|\n", environ->curr_command);
	command = trim(environ->curr_command);
	printf("execute_command: trimmed command: |%s|\n", command);
	// if (!command)
	// 	exit_minishell(environ);
	tokens = tokenize(command);
	print_tokens(tokens);
	free(command);
	// expanded_tokens = expand(tokens);
	// free_tokens(tokens);
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
