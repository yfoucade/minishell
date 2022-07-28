/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 10:23:55 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/28 13:36:53 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../neo_libft/includes/string.h"
#include "../neo_libft/includes/printf.h"
#include "../includes/childproc.h"
#include "../includes/errors.h"
#include <readline/readline.h>

int	is_delim(char *s, char *delim, int delim_len)
{
	return (!(ft_strncmp(s, delim, delim_len)));
}

int	write_to_child(char *binary_path, char *content, char **args, char **envp)
{
	int		fds[2];
	int		status;
	pid_t	pid;

	printf("cb : %d\n", check_binary(binary_path));
	if (!check_binary(binary_path))
		return (1);
	if (pipe(fds) == -1)
		return (ft_error(binary_path, PLACEHOLDER, 1));
	pid = fork();
	if (pid == -1)
		return (ft_error(binary_path, PLACEHOLDER, 1));
	if (pid == 0)
	{
		close(fds[1]);
		dup2(fds[0], 0);
		close(fds[0]);
		execve(binary_path, args, envp);
	}
	else
	{
		close(fds[0]);
		write(fds[1], content, ft_strlen(content));
		free(content);
		close(fds[1]);
		wait(&status);
	}
}

/**
 * @brief Reads a line from stdin until a delimiter is found.
 * 
 * @param delim The delimiter to look for.
 * @param binary Path to binary to execute and write to.
 * @param args Array of arguments to pass to the binary.
 * @param envp Array of environment variables to pass to the binary.
 * @return int Return code of subprocess (0 if cancelled,
 * 32767 for any other error).
 */
int	redirect_delimiter(char *delim, char *binary, char **args, char **envp)
{
	char	*content;
	char	*last_line;
	int		delim_length;
	int		line;

	line = 0;
	delim_length = ft_strlen(delim);
	last_line = readline("> ");
	if (!last_line)
		return (0x7FFF);
	if (is_delim(last_line, delim, delim_length))
		return (write_to_child(binary, last_line, args, envp));
	else
	{
		content = last_line;
		while (line++ != -1)
		{
			last_line = readline("> ");
			if (!last_line)
			{
				ft_printf("trash: warning: here-document got end-of-file at line %d, expected `%s`\n", line, delim);
				break ;
			}
			if (is_delim(last_line, delim, delim_length))
				break ;
			content = ft_strsjoin(content, "\n");
			content = ft_strsjoin(content, last_line);
		}
		return (write_to_child(binary, content, args, envp));
	}
}
