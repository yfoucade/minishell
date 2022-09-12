/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:41 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/12 22:51:23 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	lst_add_n(t_str_list **lst, char *str, char *end)
{
	t_str_list	*new;
	t_str_list	*tmp;

	new = malloc(sizeof(*new));
	if (!new)
		return (FAILURE);
	new->str = ft_strndup(str, end - str);
	if (!new->str)
	{
		free(new);
		return (FAILURE);
	}
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (SUCCESS);
}