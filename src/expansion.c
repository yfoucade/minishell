/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:54:49 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/06 23:43:27 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// if str starts with a single quote, then no expansion.
// -> return a copy.
// otherwise, do process and do not interpret single quotes.
char	*expand(t_status *status, char *str)
{
	t_str_list	*chunks;
	char		*res;

	if (*str == '\'')
		return (ft_strdup(str));
	chunks = construct_raw_linked_list(str);
	chunks = substitute_all(status, chunks);
	res = concatenate(chunks);
	free_str_list(chunks);
	return (res);
}

char	replace_by_expansion(t_status *status, char *str, char **dest)
{
	t_str_list	*three_type_split;
	t_str_list	*tmp_list;
	char		*expansion;
	char		*tmp_str;
	char		user_input_quotes;

	three_type_split = split_three_type(str);
	tmp_list = three_type_split;
	while (tmp_list)
	{
		user_input_quotes = (*tmp_list->str == '\'') + (*tmp_list->str == '"');
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
