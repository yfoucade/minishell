/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_postprocess.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:14:06 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/08 11:14:21 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	postprocess_redirections(t_status *status)
{
	if (status->out_fd != STDOUT_FILENO)
		close(status->out_fd);
	if (status->in_fd != STDIN_FILENO)
		close(status->in_fd);
	if (status->in_pipe)
	{
		if (status->in_pipe[0] != status->in_fd)
			close_pipe_end(status->in_pipe, PIPE_OUT);
		free_pipe(&status->in_pipe);
	}
	if (status->out_pipe)
	{
		if (status->out_pipe[1] != status->out_fd)
			close_pipe_end(status->out_pipe, PIPE_IN);
		status->in_pipe = status->out_pipe;
	}
	status->out_pipe = NULL;
	status->out_fd = STDOUT_FILENO;
	status->in_fd = STDIN_FILENO;
}
