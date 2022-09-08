/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:37:54 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/08 10:38:01 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_prev_pipeline(t_status *status)
{
	free(status->prev_pipeline);
	status->prev_pipeline = status->curr_pipeline;
	status->curr_pipeline = NULL;
}

void	free_curr_pipeline(t_status *status)
{
	free(status->curr_pipeline);
	status->curr_pipeline = NULL;
}

void	free_pipelines(t_status *status)
{
	free_str_list(status->pipelines);
	status->pipelines = NULL;
}
