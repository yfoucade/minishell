/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:54:49 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/15 00:35:56 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!chunks)
		return (NULL);
	chunks = substitute_all(status, chunks);
	if (!chunks)
	{
		free_str_list(chunks);
		return (NULL);
	}
	res = concatenate(chunks);
	free_str_list(chunks);
	return (res);
}

char	expand_lst(t_status *status, t_str_list *lst)
{
	char	user_input_quotes;
	char	*tmp_str;
	char	*expansion;

	while (lst)
	{
		user_input_quotes = (*lst->str == '\'') + (*lst->str == '"');
		tmp_str = expand(status, lst->str);
		if (!tmp_str)
			return (FAILURE);
		if (user_input_quotes)
			expansion = ft_strndup(tmp_str + 1, ft_strlen(tmp_str) - 2);
		else
			expansion = ft_strdup(tmp_str);
		
		free(tmp_str);
		if (!expansion)
			return (FAILURE);
		free(lst->str);
		lst->str = expansion;
		lst = lst->next;
	}
	return (SUCCESS);
}

char	replace_by_expansion(t_status *status, char *str, char **dest)
{
	t_str_list	*three_type_split;
	char		*expansion;

	three_type_split = split_three_type(str);
	if (!three_type_split)
		return (FAILURE);
	if (expand_lst(status, three_type_split))
	{
		free_str_list(three_type_split);
		return (FAILURE);
	}
	expansion = concatenate(three_type_split);
	free_str_list(three_type_split);
	if (!expansion)
		return (FAILURE);
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
