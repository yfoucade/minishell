/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:13:52 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/05 02:29:37 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_right_newline(char *s)
{
	char	*end;

	if (!s)
		return ;
	while (*s)
	{
		if (*s != '\n')
			end = s;
		s++;
	}
	end[1] = '\0';
}

void	write_until_delim(t_status *status, int fd, char *delim)
{
	char	*line;

	while (TRUE)
	{
		if (status->ft_isatty)
			line = readline(PS2);
		else
		{
			line = get_next_line(STDIN_FILENO);
			trim_right_newline(line);
		}
		if (!line)
			exit(1);
		if (!ft_strcmp(line, delim))
			return ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	seek_delim(char *delim)
{
	char *line;

	line = get_next_line(STDIN_FILENO);
	trim_right_newline(line);
	while (line)
	{
		if (!ft_strcmp(line, delim))
			break;
		line = get_next_line(STDIN_FILENO);
		trim_right_newline(line);
	}
	free(line);
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
		write_until_delim(status, pipe_fd[1], delim);
		exit(0);
	}
	uninstall_handlers();
	waitpid(pid, &status->child_exit_status, 0);
	install_handlers();
	close(pipe_fd[1]);
	if (!WIFEXITED(status->child_exit_status))
	{
		status->return_value = FAILURE;
		status->exit_status = FAILURE;
		set_error_msg(status, "heredoc: Interrupted\n");
		close(pipe_fd[0]);
		return (FAILURE);
	}
	if (!status->ft_isatty)
		seek_delim(delim);
	status->in_fd = pipe_fd[0];
	return (SUCCESS);
}
