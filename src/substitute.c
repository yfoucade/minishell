/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:43:18 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/15 00:34:50 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	substitute_one(t_status *status, t_str_list *chunk)
{
	char	*value;

	if (*chunk->str != '$' || !chunk->str[1])
		return (SUCCESS);
	value = parse_name(status, chunk->str + 1);
	if (!value)
		return (FAILURE);
	free(chunk->str);
	chunk->str = value;
	return (SUCCESS);
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
