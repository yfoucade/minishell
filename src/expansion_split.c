/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 23:37:29 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/15 00:39:35 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	add_next_chunk(t_str_list **chunks, char **str)
{
	char		*end;
	t_str_list	*tmp;
	t_str_list	*new_chunk;

	end = find_chunk_end(*str);
	new_chunk = malloc(sizeof(*new_chunk));
	if (!new_chunk)
		return (FAILURE);
	new_chunk->next = NULL;
	new_chunk->str = ft_strndup(*str, end - *str);
	if (!new_chunk->str)
	{
		free(new_chunk);
		return (FAILURE);
	}
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
	return (SUCCESS);
}

t_str_list	*construct_raw_linked_list(char *str)
{
	t_str_list	*res;

	res = NULL;
	while (*str)
	{
		if (add_next_chunk(&res, &str))
		{
			free_str_list(res);
			return (NULL);
		}
	}
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
		if (lst_add(&res, tmp))
		{
			free(tmp);
			free_str_list(res);
			return (NULL);
		}
		str = end;
	}
	return (res);
}
