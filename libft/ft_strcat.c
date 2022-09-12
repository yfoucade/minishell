/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:25 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/10 11:38:40 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, char *s2)
{
	char	*res;
	char	*tmp;

	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	tmp = res;
	if (s1)
		while (*s1)
			*tmp++ = *s1++;
	if (s2)
		while (*s2)
			*tmp++ = *s2++;
	*tmp = '\0';
	return (res);
}
