/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:56:08 by jallerha          #+#    #+#             */
/*   Updated: 2022/09/19 13:40:53 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returns a mask that stores multiple informations regarding a path
 * 
 * @param path Path to something (file, folder, pseudo-file, ...)
 * @return int A mask that can tell you if you can read, write, execute, or
 *  if path is a directory.
 */
int	ft_access(char *path)
{
	int			output;
	struct stat	stat_info;

	output = NO_ACCESS;
	if (stat(path, &stat_info) == 0)
	{
		if (S_ISDIR(stat_info.st_mode))
			output |= IS_DIR;
	}
	else if (errno == ENOENT)
	{
		errno = 0;
		return (NO_ACCESS);
	}
	output |= EXISTS;
	if (access(path, R_OK) == 0)
		output |= READABLE;
	if (access(path, W_OK) == 0)
		output |= WRITEABLE;
	if (access(path, X_OK) == 0)
		output |= EXECUTABLE;
	errno = 0;
	return (output);
}
