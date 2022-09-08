/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_preprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:12:46 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/08 11:18:13 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_output(t_status *status)
{
	if (status->out_fd != STDOUT_FILENO)
		return ;
	else if (status->out_pipe)
		status->out_fd = status->out_pipe[1];
}

char	redirect_output(t_status *status, char *type, char *pathname)
{
	int	flag;
	int	mode;

	flag = O_WRONLY | O_CREAT | O_APPEND * (type[1] == '>')
		| O_TRUNC * (type[1] != '>');
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	if (status->out_fd != STDOUT_FILENO)
		close(status->out_fd);
	status->out_fd = open(pathname, flag, mode);
	if (status->out_fd == -1)
	{
		status->out_fd = STDOUT_FILENO;
		status->return_value = FAILURE;
		status->exit_status = errno;
		set_error_msg(status, strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}

char	input_from_file(t_status *status, char *path)
{
	status->in_fd = open(path, O_RDONLY);
	if (status->in_fd == -1)
	{
		status->in_fd = STDIN_FILENO;
		status->return_value = FAILURE;
		status->exit_status = errno;
		set_error_msg(status, strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}

char	redir_input(t_status *status, char *type, char *path_or_delim)
{
	char	ret;

	if (status->in_fd != STDIN_FILENO)
		close(status->in_fd);
	if (status->in_pipe)
	{
		close_pipe_end(status->in_pipe, PIPE_OUT);
		free_pipe(&status->in_pipe);
	}
	if (type[1] == '<')
		ret = create_heredoc(status, path_or_delim);
	else
		ret = input_from_file(status, path_or_delim);
	return (ret);
}

char	preprocess_redirections(t_status *status)
{
	char	**redirs;
	char	ret;

	if (status->curr_command->next)
		create_pipe(&status->out_pipe);
	redirs = status->redirections;
	while (*redirs)
	{
		if (**redirs == '>')
			ret = redirect_output(status, *redirs, *(redirs + 1));
		else
			ret = redir_input(status, *redirs, *(redirs + 1));
		redirs += 2;
		if (ret)
			return (FAILURE);
	}
	return (SUCCESS);
}
