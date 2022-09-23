/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:31:00 by jallerha          #+#    #+#             */
/*   Updated: 2022/09/21 12:31:02 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strnlen(char *s, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (s[i] && i < n)
		i++;
	return (i);
}
