/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:50:35 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/25 14:09:14 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	pwd(t_status *status)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_putfd(path, status->out_fd);
		ft_putfd("\n", status->out_fd);
		free(path);
		return (SUCCESS);
	}
	else if (errno)
	{
		status->exit_status = errno;
		set_error_msg(status, strerror(errno));
		flush_error_msg(status, NULL);
	}
	else
	{
		status->exit_status = FAILURE;
		set_error_msg(status, "pwd: Unknown error\n");
		flush_error_msg(status, NULL);
	}
	return (FAILURE);
}
