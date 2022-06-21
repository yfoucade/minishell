/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:43 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/21 10:26:06 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decide_add_history(t_environ *environ)
{
	if (is_blank_str(environ->curr_command))
		return ;
	if (!(environ->last_command))
	{
		add_history(environ->curr_command);
		return ;
	}
	if (ft_strcmp(environ->last_command, environ->curr_command))
		add_history(environ->curr_command);
}
