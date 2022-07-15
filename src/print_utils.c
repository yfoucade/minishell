/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:49:50 by yfoucade          #+#    #+#             */
/*   Updated: 2022/07/14 23:58:35 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_str_list(t_str_list *str_list)
{
	while (str_list)
	{
		DEBUG(str_list->str);
		str_list = str_list->next;
	}
}