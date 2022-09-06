/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:50:35 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/06 18:21:17 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_status *status)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_putfd(path, status->out_fd);
		ft_putfd("\n", status->out_fd);
		free(path);
		return ;
	}
	else if (errno)
	{
		status->exit_status = errno;
		status->return_value = errno;
		set_error_msg(status, strerror(errno));
	}
	else
	{
		status->exit_status = FAILURE;
		status->return_value = FAILURE;
		set_error_msg(status, "pwd: Unknown error\n");
	}
}
