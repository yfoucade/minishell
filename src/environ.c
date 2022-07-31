/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:06:03 by yfoucade          #+#    #+#             */
/*   Updated: 2022/07/31 05:07:52 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo: malloc for each field.
void	init_environ(t_environ *environ_)
{
	environ_->path = malloc(sizeof(environ_->path));
	environ_->argv = NULL;
	environ_->input = NULL;
	environ_->pipelines = NULL;
	environ_->curr_command = NULL;
	environ_->last_command = NULL;
	environ_->exit_status = 0;
}

void	update_environ(t_environ *environ_)
{
	environ_->path = getenv("PATH");
}

void	free_environ(t_environ *environ_)
{
	free(environ_->path);
	free(environ_->curr_command);
	free(environ_->last_command);
}
