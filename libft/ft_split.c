/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:18 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/06 16:33:57 by yfoucade         ###   ########.fr       */
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
		res = lst_add_n(&res, str, end);
		str = end + (*end == c);
	}
	return (res);
}
