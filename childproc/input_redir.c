/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:12:19 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/25 15:53:24 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/childproc.h"
#include "../includes/errors.h"

/**
 * @brief Check if binary exists, and is executable, same for the file.
 * If the file is readable, opens and write fd to `file_fd`.
 * If any error, they will be printed to stderr.
 * @param binary_path Path to binary that needs to be executed
 * @param file_path Path to file that needs to be read
 * @param file_fd Pointer to input file descriptor
 * @return int 0 if all conditions are met, something else otherwise
 */
int	checks(char *binary_path, char *file_path, int *file_fd)
{
	int	bin_mask;
	int	file_mask;

	bin_mask = ft_access(binary_path);
	file_mask = ft_access(file_path);
	if (!(bin_mask & EXISTS))
		return (ft_error(binary_path, NOT_FOUND, 1));
	if (!(bin_mask & EXECUTABLE))
		return (ft_error(binary_path, PERMISSION_DENIED, 1));
	if (!(file_mask & EXISTS))
		return (ft_error(file_path, NOT_FOUND, 1));
	if (!(file_mask & READABLE))
		return (ft_error(file_path, PERMISSION_DENIED, 1));
	*file_fd = open(file_path, O_RDONLY);
	if (*file_fd == -1)
		return (ft_error(file_path, OPEN_FAILED, 1));
	return (0);
}

/**
 * @brief Takes a file and a binary, and writes file's content to subprocess'
 * stdin.
 * 
 * @param command The command to redirect input to.
 * @param file The file to read from.
 * @param args The arguments to the command.
 * @param envp The environment to pass to the command.
 * @return int Subprocess' exit status.
 */
int	redirect_input(char *command, char *file, char **args, char **envp)
{
	int		file_fd;
	pid_t	pid;
	int		status;

	file_fd = 0;
	if (checks(command, file, &file_fd))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		dup2(file_fd, 0);
		execve(command, args, envp);
		exit(0);
	}
	else
	{
		wait(&status);
		return (status);
	}
}
