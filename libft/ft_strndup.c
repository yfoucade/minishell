/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:34 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/10 11:22:27 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	char	*res;
	int		i;

	if (!str || n < 0)
		return (NULL);
	res = malloc(n + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < n && str[i])
	{
		res[i] = str[i];
		++i;
	}
	res[i] = '\0';
	return (res);
}
