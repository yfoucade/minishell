/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:13:45 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/20 12:55:38 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	char	**tmp;

	if (!array)
		return ;
	tmp = array;
	while (*tmp)
	{
		free(*tmp);
		++tmp;
	}
	free(array);
}