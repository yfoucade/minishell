/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:18 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/12 16:22:08 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str_list	*ft_split(char *str, char c)
{
	t_str_list	*res;
	char		*end;

	res = NULL;
	while (*str)
	{
		end = str;
		while (*end && *end != c)
			++end;
		if (lst_add_n(&res, str, end))
		{
			free_str_list(res);
			return (NULL);
		}
		str = end + (*end == c);
	}
	return (res);
}
