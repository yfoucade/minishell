/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:43 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/13 00:48:23 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decide_add_history(t_status *status)
{
	if (is_blank_str(status->curr_pipeline))
		return ;
	if (!(status->prev_pipeline))
	{
		add_history(status->curr_pipeline);
		return ;
	}
	if (ft_strcmp(status->prev_pipeline, status->curr_pipeline))
		add_history(status->curr_pipeline);
}
