/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:06:03 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/11 14:32:46 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo: malloc for each field.
void	init_environ(t_environ *environ_)
{
	environ_->argv = NULL;
	environ_->input = NULL;
	environ_->pipelines = NULL;
	environ_->curr_command = NULL;
	environ_->last_command = NULL;
	environ_->exit_status = 0;
}

void	free_environ(t_environ *environ_)
{
	free(environ_->curr_command);
	free(environ_->last_command);
}
