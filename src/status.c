/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:06:03 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/12 12:45:02 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_status(t_status *status_)
{
	status_->input = NULL;
	status_->pipelines = NULL;
	status_->curr_command = NULL;
	status_->last_command = NULL;
	status_->exit_status = 0;
}

void	free_status(t_status *status)
{
	free(status->input);
	free_str_list(status->pipelines);
	free(status->curr_command);
	free(status->last_command);
	free(status);
}
