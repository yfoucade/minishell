/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_unquoted_c.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:15 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/15 04:05:56 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str_list	*ft_split_unquoted_c(char *str, char c)
{
	t_str_list	*res;
	char		*chunk_end;

	if (!str || *str == '|' || str[ft_strlen(str) - 1] == '|')
		return (NULL);
	res = NULL;
	while (TRUE)
	{
		chunk_end = str;
		while (*chunk_end && *chunk_end != c)
		{
			if (*chunk_end == '"' || *chunk_end == '\'')
				chunk_end = ft_strchr(chunk_end + 1, *chunk_end);
			if (!*chunk_end)
				break ;
			chunk_end++;
		}
		if (lst_add_n(&res, str, chunk_end))
			return (free_str_list(res), NULL);
		str = chunk_end + (*chunk_end == c);
		if (!*str)
			break ;
	}
	return (res);
}
