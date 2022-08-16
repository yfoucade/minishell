/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:28:07 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/16 11:22:56 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_list(t_str_list *str_list)
{
	t_str_list	*tmp;

	while (str_list)
	{
		tmp = str_list->next;
		free(str_list->str);
		free(str_list);
		str_list = tmp;
	}
}