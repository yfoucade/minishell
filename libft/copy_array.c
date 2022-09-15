/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 03:42:35 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/15 03:42:49 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	copy_array_values(char **old, char **new)
{
	if (!old || !new)
		return ;
	while (*old)
		*(new++) = *(old++);
	*new = NULL;
}
