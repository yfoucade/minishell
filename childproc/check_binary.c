/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:14:01 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/28 13:34:56 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/childproc.h"
#include "../includes/errors.h"

/**
 * @brief Check if binary exists, and is executable
 * Display error message if necessary
 * @param path Path to binary
 * @return int 0 if exists, and can be executed, 1 otherwise
 */
int	check_binary(char *path)
{
	int	access_mask;

	access_mask = ft_access(path);
	if (!(access_mask & EXISTS))
		return (ft_error(path, NOT_FOUND, 1));
	if (access_mask & IS_DIR)
		return (ft_error(path, IS_A_DIR, 1));
	if (!(access_mask & EXECUTABLE))
		return (ft_error(path, NOT_EXECUTABLE, 1));
	return (0);
}