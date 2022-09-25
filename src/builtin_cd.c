/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:08:26 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/25 13:50:11 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	cd(t_status *status)
{
	int	ret;

	ret = array_size(status->args);
	if (ret == 1)
	{
		set_error_msg(status, "cd: missing directory\n");
		flush_error_msg(status, NULL);
		return (FAILURE);
	}
	ret = chdir(status->args[1]);
	if (ret == -1)
	{
		status->return_value = errno;
		status->exit_status = errno;
		perror("minishell: cd");
		errno = 0;
		return (FAILURE);
	}
	return (SUCCESS);
}
