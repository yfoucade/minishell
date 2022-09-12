/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_startswith.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:20 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/10 11:43:22 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_startswith(char *little, char *big)
{
	if (!little)
		return (TRUE);
	if (!big)
		return (FALSE);
	while (*little)
		if (*little++ != *big++)
			return (FALSE);
	return (TRUE);
}
