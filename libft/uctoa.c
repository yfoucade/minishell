/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uctoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:46:33 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/15 00:49:12 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*uctoa(unsigned char n)
{
	char	*res;
	int		i;

	res = malloc(4);
	if (!res)
		return (NULL);
	i = 0;
	if (n >= 100)
		res[i++] = '0' + n / 100;
	n %= 100;
	if (i || n >= 10)
		res[i++] = '0' + n / 10;
	n %= 10;
	res[i++] = '0' + n;
	res[i] = '\0';
	return (res);
}
