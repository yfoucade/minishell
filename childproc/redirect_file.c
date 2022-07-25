/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:44:47 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/25 15:09:11 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/childproc.h"
#include "../includes/errors.h"

/**
 * @brief Checks that binary exists, and is executable
 * 
 * @param bin_path Path to binary
 * @return int Returns 1 if everything is ok, something else otherwise
 */
int	check_binary(char *bin_path)
{
	int	access_mask;

	access_mask = ft_access(bin_path);
	if (!(access_mask & EXISTS))
		return (ft_error(bin_path, NOT_FOUND, -1));
	if (access_mask & IS_DIR)
		return (ft_error(bin_path, IS_A_DIR, -1));
	if (!(access_mask & EXECUTABLE))
		return (ft_error(bin_path, PERMISSION_DENIED, -1));
	return (1);
}

/**
 * @brief Tries to create a file
 * 
 * @param path Path to file to create
 * @param append If non 0, the file will be opened in append mode
 * @return int A file descriptor with WRITE permissions (and append if passed)
 * (returns -1 if error, with a printed error)
 */
int	open_file_write(char *path, int append)
{
	int	fd;
	int	mask;

	mask = O_WRONLY | O_CREAT | O_CREAT 
		| (O_TRUNC * (append == 0)) | (O_APPEND * append);
	fd = open(path, mask, 0644);
	if (fd == -1)
		return ft_error(path, PERMISSION_DENIED, -1);
	return (fd);
}

/**
 * @brief Check conditions for redirecting process' output to a file
 * 
 * @param output_file File to redirect to (will be created if necessary)
 * @return int Returns a file descriptor to a file, or a negative number matching
 * an error (that'll be printed)
 */
int	prepare_file(char *output_file, int append)
{
	int	access_mask;
	int	fd;

	access_mask = ft_access(output_file);
	fd = -1;
	if (access_mask & EXISTS)
	{
		if (access_mask & IS_DIR)
			return ft_error(output_file, IS_A_DIR, -1);
		if (!(access_mask & WRITEABLE))
			return ft_error(output_file, PERMISSION_DENIED, -1);
	}
	fd = open_file_write(output_file, append);
	if (fd > 0)
		return (fd);
	else
		return (-1);
}

int	redirect_to_file(char *binary_path, char **args, char **envp, char *output)
{
	int	fd;
	int	fds[2];
	int	error_code;

	fd = prepare_file(output, 0);
	if (fd <= -1)
		return (-1);
	if (check_binary(binary_path) != 1)
		return (-1);
	fds[0] = fd;
	fds[1] = 2;
	error_code = redir_open(binary_path, args, envp, fds);
	close(fd);
	return (error_code);
}

int	redirect_append(char *binary_path, char **args, char **envp, char *output)
{
	int	fd;
	int	fds[2];
	int	error_code;

	fd = prepare_file(output, 1);
	if (fd <= -1)
		return (-1);
	if (check_binary(binary_path) != 1)
		return (-1);
	fds[0] = fd;
	fds[1] = 2;
	error_code = redir_open(binary_path, args, envp, fds);
	close(fd);
	return (error_code);
}