/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:13:52 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/01 11:04:53 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	write_until_delim(int	fd, char *delim)
{
	char	*line;

	while (TRUE)
	{
		line = readline(PS2);
		if (!ft_strcmp(line, delim))
			return ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

char	create_heredoc(t_status *status, char *delim)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (!pid)
	{
		heredoc_handlers();
		close(pipe_fd[0]);
		write_until_delim(pipe_fd[1], delim);
		exit(0);
	}
	uninstall_handlers();
	waitpid(pid, &status->child_exit_status, 0);
	install_handlers();
	close(pipe_fd[1]);
	if (WIFSTOPPED(status->child_exit_status))
	{
		printf("\n");
		status->return_value = FAILURE;
		status->exit_status = FAILURE;
		set_error_msg(status, "heredoc: Interrupted\n");
		close(pipe_fd[0]);
		return (FAILURE);
	}
	status->in_fd = pipe_fd[0];
	return (SUCCESS);
}
