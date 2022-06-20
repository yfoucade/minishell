/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:06:03 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/20 22:21:44 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo: malloc for each field.
void	init_environ(t_environ *environ)
{
	environ->path = malloc(sizeof(environ->path));
	environ->curr_command = NULL;
	environ->last_command = NULL;
	environ->exit_status = 0;
}

void	update_environ(t_environ *environ)
{
	environ->path = getenv("PATH");
}

void	free_environ(t_environ *environ, int mask)
{
	(void)mask;
	free(environ->path);
}
