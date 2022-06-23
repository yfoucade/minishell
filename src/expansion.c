/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:54:49 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/23 18:32:46 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_variable_end(char *s)
{
	char	*closing;

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
	while (*s && !ft_strchr_chr(" \t\"'<|>$", *s))
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

char	*get_value(char *name)
{
	if ('0' <= *name && *name <= '9')
		return (ft_strdup("minishell", 10 * (*name == '0')));
	return (getenv(name));
}

char	*parse_name(char *str)
{
	int		len;
	char	*name;
	char	*value;

	len = ft_strlen(str);
	if (len > 1 && ft_strchr_chr("'\"", *str))
	{
		if (str[len - 1] == *str)
			return (ft_strdup(str + 1, len - 2));
		else
			name = ft_strdup(str, len);
	}
	else if (*str == '{' && str[len - 1] == '}')
			name = ft_strdup(str + 1, len - 2);
	else
		name = ft_strdup(str, len);
	value = get_value(name);
	free(name);
	return (value);
}

char	substitute_one(t_token *chunk)
{
	char	*value;

	if (*chunk->token != '$' || !chunk->token[1])
		return (0);
	value = parse_name(chunk->token + 1);
	free(chunk->token);
	chunk->token = value;
	return (0);
}

t_token	*substitute_all(t_token *chunks)
{
	t_token	*tmp;

	tmp = chunks;
	while (tmp)
	{
		if (substitute_one(tmp))
		{
			// free_tokens(chunks);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (chunks);
}

int	get_total_size(t_token *chunks)
{
	int		res;
	char	*tmp;

	res = 0;
	while (chunks)
	{
		if (!chunks->token)
		{
			chunks = chunks->next;
			continue ;
		}
		tmp = chunks->token;
		while (*tmp++)
			res++;
		chunks = chunks->next;
	}
	return (res);
}

void	fill(char *res, t_token *chunks)
{
	char	*tmp;

	while (chunks)
	{
		if (!chunks->token)
		{
			chunks = chunks->next;
			continue ;
		}
		tmp = chunks->token;
		while (*tmp)
			*res++ = *tmp++;
		chunks = chunks->next;
	}
	*res = '\0';
}

char	*concatenate(t_token *chunks)
{
	char	*res;
	int		size;

	size = get_total_size(chunks);
	res = malloc(size + 1);
	fill(res, chunks);
	return (res);
}

char	*expand(char *command)
{
	t_token	*chunks;
	char	*res;

	chunks = construct_raw_linked_list(command);
	print_tokens(chunks);
	chunks = substitute_all(chunks);
	// print_tokens(chunks);
	res = concatenate(chunks);
	// printf("%s\n", res);
	//free_tokens(chunks);
	return (res);
}
