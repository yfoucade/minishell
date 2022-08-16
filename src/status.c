/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:06:03 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/16 11:35:39 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_status(t_status *status)
{
	status->input = NULL;
	status->pipelines = NULL;
	status->in_pipe = NULL;
	status->out_pipe = NULL;
	status->curr_command = NULL;
	status->last_command = NULL;
	status->command = NULL;
	status->exit_status = 0;
}

void	free_status(t_status *status)
{
	free(status->input);
	free_str_list(status->pipelines);
	free(status->curr_command);
	free(status->last_command);
	free(status);
}

void	save_last_command(t_status *status)
{
	free(status->last_command);
	status->last_command = status->curr_command;
	status->curr_command = NULL;
}

void	free_curr_command(t_status *status)
{
	free(status->curr_command);
	status->curr_command = NULL;
}

void	free_pipelines(t_status *status)
{
	free_str_list(status->pipelines);
	status->pipelines = NULL;
}

void	free_pipe(int **tab)
{
	free(*tab);
	*tab = NULL;
}

void	create_pipe(int **tab)
{
	*tab = malloc(sizeof(**tab) * 2);
	pipe(*tab);
}

void	close_pipe_end(int *tab, int end)
{
	close(tab[end]);
}
