/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:54:49 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/26 16:54:21 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_variable_end(char *s)
{
	char	*closing;

	if (*s == '?')
		return (s + 1);
	if (*s == '_' || ft_is_alpha(*s))
	{
		while (ft_is_alnum(*s) || *s == '_')
			s++;
		return (s);
	}
	if (*s == '{')
	{
		closing = ft_strchr(s + 1, '}');
		if (*closing == '}')
			return (closing + 1);
	}
	return (s);
}

char	*find_constant_end(char *command)
{
	while (*command)
	{
		if (*command == '$')
			return (command);
		++command;
	}
	return (command);
}

char	*find_chunk_end(char *command)
{
	if (*command == '$')
		return (find_variable_end(command + 1));
	else
		return (find_constant_end(command));
}

void	add_next_chunk(t_str_list **chunks, char **str)
{
	char	*end;
	t_str_list	*tmp;
	t_str_list	*new_chunk;

	end = find_chunk_end(*str);
	new_chunk = malloc(sizeof(*new_chunk));
	new_chunk->next = NULL;
	new_chunk->str = ft_strndup(*str, end - *str);
	*str = end;
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

t_str_list	*construct_raw_linked_list(char *str)
{
	t_str_list	*res;

	res = NULL;
	while (*str)
	{
		add_next_chunk(&res, &str);
	}
	return (res);
}

char	*get_value(t_status *status, char *name)
{
	if ('0' <= *name && *name <= '9')
		return (ft_strndup("minishell", 10 * (*name == '0')));
	return (ft_strdup(ft_getenv(status, name)));
}

char	*uctoa(unsigned char n)
{
	char	*res;
	int		i;

	res = malloc(4);
	i = 0;
	if (n >= 100)
		res[i++] = '0' + n / 100;
	n %= 100;
	if (i || n >= 10)
		res[i++] = '0' + n / 10;
	n %= 10;
	res[i++] = '0' + n;
	res[i] = '\0';
	return (res);
}

// str = "?" or "name" or "{name}"
char	*parse_name(t_status *status, char *str)
{
	int		len;
	char	*name;
	char	*value;

	name = NULL;
	len = ft_strlen(str);
	if (*str == '?')
		return (uctoa(status->exit_status));
	else if (*str == '{')
	{
		name = ft_strndup(str + 1, len - 2);
		if (!is_valid_identifier(name))
		{
			free(name);
			status->return_value = FAILURE;
			status->exit_status = FAILURE;
			set_error_msg(status, "invalid identifier\n");
			return (NULL);
		}
	}
	else
		name = ft_strdup(str);
	value = get_value(status, name);
	free(name);
	return (value);
}

char	*old_parse_name(t_status *status, char *str)
{
	int		len;
	char	*name;
	char	*value;

	len = ft_strlen(str);
	if (len > 1 && ft_strchr_chr("'\"", *str))
	{
		if (str[len - 1] == *str)
			return (ft_strndup(str + 1, len - 2));
		else
			name = ft_strndup(str, len);
	}
	else if (*str == '{' && str[len - 1] == '}')
			name = ft_strndup(str + 1, len - 2);
	else
		name = ft_strndup(str, len);
	value = get_value(status, name);
	free(name);
	return (value);
}

char	substitute_one(t_status *status, t_str_list *chunk)
{
	char	*value;

	if (*chunk->str != '$' || !chunk->str[1])
		return (0);
	value = parse_name(status, chunk->str + 1);
	free(chunk->str);
	chunk->str = value;
	return (0);
}

t_str_list	*substitute_all(t_status *status, t_str_list *chunks)
{
	t_str_list	*tmp;

	tmp = chunks;
	while (tmp)
	{
		if (substitute_one(status, tmp))
		{
			free_str_list(chunks);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (chunks);
}

int	get_total_size(t_str_list *chunks)
{
	int		res;
	char	*tmp;

	res = 0;
	while (chunks)
	{
		if (!chunks->str)
		{
			chunks = chunks->next;
			continue ;
		}
		tmp = chunks->str;
		while (*tmp++)
			res++;
		chunks = chunks->next;
	}
	return (res);
}

void	fill(char *res, t_str_list *chunks)
{
	char	*tmp;

	while (chunks)
	{
		if (!chunks->str)
		{
			chunks = chunks->next;
			continue ;
		}
		tmp = chunks->str;
		while (*tmp)
			*res++ = *tmp++;
		chunks = chunks->next;
	}
	*res = '\0';
}

char	*concatenate(t_str_list *chunks)
{
	char	*res;
	int		size;

	size = get_total_size(chunks);
	res = malloc(size + 1);
	fill(res, chunks);
	return (res);
}

// if str starts with a single quote, then no expansion.
// -> return a copy.
// otherwise, do process and do not interpret single quotes.
char	*expand(t_status *status, char *str)
{
	t_str_list	*chunks;
	char	*res;

	if (*str == '\'')
		return (ft_strdup(str));
	chunks = construct_raw_linked_list(str);
	chunks = substitute_all(status, chunks);
	res = concatenate(chunks);
	free_str_list(chunks);
	return (res);
}

t_str_list	*split_three_type(char *str)
{
	t_str_list	*res;
	char		*end;
	char		*tmp;

	res = NULL;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			end = ft_strchr(str + 1, *str) + 1;
		else
		{
			end = str + 1;
			while (*end && *end != '\'' && *end != '"')
				++end;
		}
		tmp = ft_strndup(str, end - str);
		res = lst_add(&res, tmp);
		free(tmp);
		str = end;
	}
	return (res);
}

char	replace_by_expansion(t_status *status, char *str, char **dest)
{
	t_str_list	*three_type_split;
	t_str_list	*tmp_list;
	char	*expansion;
	char	*tmp_str;
	char	user_input_quotes;

	three_type_split = split_three_type(str);
	tmp_list = three_type_split;
	while (tmp_list)
	{
		user_input_quotes = *tmp_list->str == '\'' || *tmp_list->str == '"';
		tmp_str = expand(status, tmp_list->str);
		if (user_input_quotes)
			expansion = ft_strndup(tmp_str + 1, ft_strlen(tmp_str) - 2);
		else
			expansion = ft_strdup(tmp_str);
		free(tmp_str);
		free(tmp_list->str);
		tmp_list->str = expansion;
		tmp_list = tmp_list->next;
	}
	expansion = concatenate(three_type_split);
	free_str_list(three_type_split);
	free(*dest);
	*dest = expansion;
	return (SUCCESS);
}

char	expand_array_elements(t_status *status, char **array)
{
	while (*array)
	{
		if (replace_by_expansion(status, *array, array))
			return (FAILURE);
		++array;
	}
	return (SUCCESS);
}
