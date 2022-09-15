/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:45 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/14 23:15:17 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**lst_to_array(t_str_list *lst)
{
	char		**res;
	char		**tmp_arr;
	t_str_list	*tmp_lst;
	int			count;

	tmp_lst = lst;
	count = 0;
	while (tmp_lst)
	{
		++count;
		tmp_lst = tmp_lst->next;
	}
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	tmp_arr = res;
	tmp_lst = lst;
	while (tmp_lst)
	{
		*tmp_arr++ = ft_strdup(tmp_lst->str);
		if (!*(tmp_arr - 1))
		{
			free_array(res);
			return (NULL);
		}
		tmp_lst = tmp_lst->next;
	}
	*tmp_arr = NULL;
	return (res);
}
