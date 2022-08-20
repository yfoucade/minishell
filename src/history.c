/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:43 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/19 17:56:15 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decide_add_history(t_status *environ)
{
	if (is_blank_str(environ->curr_pipeline))
		return ;
	if (!(environ->prev_pipeline))
	{
		add_history(environ->curr_pipeline);
		return ;
	}
	if (ft_strcmp(environ->prev_pipeline, environ->curr_pipeline))
		add_history(environ->curr_pipeline);
}
