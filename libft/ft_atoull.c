/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:52:08 by jallerha          #+#    #+#             */
/*   Updated: 2022/09/22 12:04:10 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Parse an unsigned long long and sets sign_flag to non-zero if 
 * the string was supposed to be negative
 * 
 * @param s String to parse
 * @param sign_flag Pointer to an integer that will be set to non-zero
 * if the string was supposed to be negative
 * @return unsigned long long Parsed number
*/
unsigned long long	ft_atoull(const char *s, int *sign_flag)
{
	int					i;
	unsigned long long	n;

	i = 0;
	n = 0;
	while (is_blank_chr(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			*sign_flag = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + s[i] - '0';
		i++;
	}
	return (n);
}
