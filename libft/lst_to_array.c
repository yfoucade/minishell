/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:45 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/15 03:57:35 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	lst_size(t_str_list *lst)
{
	int	res;

	if (!lst)
		return (0);
	res = 0;
	while (lst)
	{
		++res;
		lst = lst->next;
	}
	return (res);
}

char	**lst_to_array(t_str_list *lst)
{
	char		**res;
	char		**tmp_arr;

	res = malloc(sizeof(char *) * (lst_size(lst) + 1));
	if (!res)
		return (NULL);
	tmp_arr = res;
	while (lst)
	{
		*tmp_arr++ = ft_strdup(lst->str);
		if (!*(tmp_arr - 1))
		{
			free_array(res);
			return (NULL);
		}
		lst = lst->next;
	}
	*tmp_arr = NULL;
	return (res);
}
