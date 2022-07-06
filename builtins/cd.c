/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:14:44 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/06 21:38:41 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "../neo_libft/includes/printf.h"

// TODO: Remplacer par une liste de tokens (ou autre)
int	ft_change_directory(char *target)
{
	int		err;

	err = chdir(target);
	if (err != -1)
		return (0);
	if (errno == EACCES)
		ft_fprintf(STDERR_FILENO, "cd : Permission denied\n");
	else if (errno == ENOENT)
		ft_fprintf(STDERR_FILENO, "cd : No such file or directory\n");
	else if (errno == ENOTDIR)
		ft_fprintf(STDERR_FILENO, "cd : Cannot cd into a file\n");
	else if (errno == EROFS)
		ft_fprintf(STDERR_FILENO, "cd : Read-only file system\n");
	else
		ft_fprintf(STDERR_FILENO, "cd : Unknown error\n");
	return (1);
}
