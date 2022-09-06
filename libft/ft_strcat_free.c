/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:23 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/06 16:34:16 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_free(char *s1, char *s2, char free_s1, char free_s2)
{
	char	*res;

	res = ft_strcat(s1, s2);
	if (!res)
		return (NULL);
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (res);
}
