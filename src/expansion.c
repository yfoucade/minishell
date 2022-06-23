/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:54:49 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/23 16:05:56 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_variable_end(char *s)
{
	char	*closing;

	if (!*s || ft_strchr_chr("<|> \t", *s))
		return (s);
	if (is_digit(*s))
		return (s + 1);
	if (*s == '\'' || *s == '"')
	{
		closing = ft_strchr(s + 1, *s);
		if (*closing == *s)
			return (closing + 1);
	}
	if (*s == '{')
	{
		closing = ft_strchr(s + 1, '}');
		if (*closing == '}')
			return (closing + 1);
	}
	while (*s && !ft_strchr_chr(" \t\"'<|>", *s))
		s++;
	return (s);
}

char	*find_constant_end(char *command)
{
	char	*closing_single_quote;

	while (*command)
	{
		if (*command == '$')
			return (command);
		if (*command != '\'')
			command++;
		else
		{
			closing_single_quote = ft_strchr(command + 1, *command);
			if (*closing_single_quote == *command)
				command = closing_single_quote + 1;
			else
				command++;
		}
	}
	return (command);
}

char	*find_chunk_end(char *command)
{
	if (*command != '$')
		return (find_constant_end(command));
	else
		return (find_variable_end(command + 1));
}

void	add_next_chunk(t_token **chunks, char **command)
{
	char	*end;
	t_token	*tmp;
	t_token	*new_chunk;

	end = find_chunk_end(*command);
	new_chunk = malloc(sizeof(new_chunk));
	new_chunk->next = NULL;
	new_chunk->token = ft_strdup(*command, end - *command);
	*command = end;
	if (!*chunks)
		*chunks = new_chunk;
	else
	{
		tmp = *chunks;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_chunk;
	}
}

t_token	*construct_raw_linked_list(char *command)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	res = NULL;
	while (*command)
	{
		add_next_chunk(&res, &command);
	}
	return (res);
}

char	*concatenate(t_token *chunks)
{
	(void)chunks;
	return (NULL);
}

char	*expand(char *command)
{
	t_token	*chunks;
	char	*res;

	chunks = construct_raw_linked_list(command);
	print_tokens(chunks);
	// chunks = substitute(chunks);
	res = concatenate(chunks);
	//free_tokens(chunks);
	return (res);
}
