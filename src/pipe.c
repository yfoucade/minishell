/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:41:17 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/27 15:03:02 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	close_pipes(t_status *status)
{
	if (status->in_pipe)
		close(status->in_pipe[0]);
	close(status->in_fd);
	if (status->out_pipe)
		close(status->out_pipe[1]);
	close(status->out_fd);
}