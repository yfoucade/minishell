/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:52:08 by jallerha          #+#    #+#             */
/*   Updated: 2022/09/18 22:23:54 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int		signe;
	int		i;
	long	n;

	signe = 1;
	i = 0;
	n = 0;
	while (is_blank_chr(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			signe = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (n * signe > 2147483647)
			return (-1);
		else if (n * signe < -2147483648)
			return (0);
		n = n * 10 + s[i] - '0';
		i++;
	}
	return (n * signe);
}