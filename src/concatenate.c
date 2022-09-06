/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 23:43:31 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/06 23:43:39 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
