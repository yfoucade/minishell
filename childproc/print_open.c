/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:21:01 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/03 22:34:09 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/childproc.h"

/**
 * @brief Creates a child-process and redirect stderr, stdout to
 * current standard error, standard output. Returns subprocess exit code.
 * Waits for the child-process to finish.
 * 
 * @param path Path of the binary to execute.
 * @param argv Arguments to pass to the binary
 * @param envp Environment variables to pass to the binary
 * @return int Exit code
 */
int	print_open(char *path, char **argv, char **envp)
{
	int fds[2];

	fds[0] = dup(1);
	fds[1] = dup(2);
	return (redir_open(path, argv, envp, fds));
}
