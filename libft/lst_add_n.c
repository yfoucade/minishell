/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:41 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/06 16:36:03 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str_list	*lst_add_n(t_str_list **lst, char *str, char *end)
{
	t_str_list	*res;
	t_str_list	*tmp;

	res = malloc(sizeof(*res));
	res->str = ft_strndup(str, end - str);
	res->next = NULL;
	if (!*lst)
		return (res);
	tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = res;
	return (*lst);
}
