/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:25:47 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/03 22:39:24 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/childproc.h"

/**
 * @brief Spawns a child-process and redirects standard outputs
 * to a file descriptor. Returns subprocess exit code.
 * Waits for the child-process to finish.
 * 
 * @param path Path of the binary to execute.
 * @param argv Arguments to pass to the binary
 * @param envp Environment variables to pass to the binary
 * @param fds File descriptor to redirect standard outputs to.
 * (fds[0] = stdout, fds[1] = stderr)
 * @return int 
 */
int	redir_open(char *path, char **argv, char **envp, int fds[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		dup2(fds[0], 1);
		dup2(fds[1], 2);
		execve(path, argv, envp);
		exit(0);
	}
	else
	{
		wait(&status);
		return (status);
	}
}
