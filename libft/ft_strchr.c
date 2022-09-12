/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:27 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/10 11:46:50 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *haystack, char needle)
{
	if (!haystack)
		return (NULL);
	while (*haystack && *haystack != needle)
		haystack++;
	return (haystack);
}
