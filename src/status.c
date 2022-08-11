/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:06:03 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/11 17:18:52 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo: malloc for each field.
void	init_status(t_status *status_)
{
	status_->input = NULL;
	status_->pipelines = NULL;
	status_->curr_command = NULL;
	status_->last_command = NULL;
	status_->exit_status = 0;
}

void	free_environ(t_status *status_)
{
	free(status_->curr_command);
	free(status_->last_command);
}
