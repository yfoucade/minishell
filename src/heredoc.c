/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:13:52 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/25 04:08:03 by yfoucade         ###   ########.fr       */
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
			line = readline(ft_getenv(status, "PS2"));
		else
			line = get_next_line(STDIN_FILENO);
		trim_right_newline(line);
		if (!line)
		{
			free_parsed_command(status);
			free_status(status);
			exit(0);
		}
		if (!ft_strcmp(line, delim))
		{
			free(line);
			return ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	seek_delim(char *delim)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	trim_right_newline(line);
	while (line)
	{
		if (!ft_strcmp(line, delim))
			break ;
		free(line);
		line = get_next_line(STDIN_FILENO);
		trim_right_newline(line);
	}
	free(line);
}

void	heredoc(t_status *status, int pipe_fd[2], char *delim)
{
	heredoc_handlers(status);
	close(pipe_fd[0]);
	write_until_delim(status, pipe_fd[1], delim);
	free_parsed_command(status);
	free_status(status);
	exit(0);
}

char	create_heredoc(t_status *status, char *delim)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (!pid)
		heredoc(status, pipe_fd, delim);
	waiting_handlers(status);
	waitpid(pid, &status->child_exit_status, 0);
	install_handlers(status);
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
