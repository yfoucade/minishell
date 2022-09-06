/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:13:45 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/06 17:59:52 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(char **array)
{
	char	**tmp;

	if (!array)
		return ;
	tmp = array;
	while (*tmp)
		free(*tmp++);
	free(array);
}
