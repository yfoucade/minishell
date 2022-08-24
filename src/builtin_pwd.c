/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:50:35 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/23 14:12:50 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_status *status)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_putstr(path);
		free(path);
		return ;
	}
	else if (errno)
	{
		status->exit_status = errno;
		status->return_value = errno;
		perror("pwd"); // no redirection of stderr
	}
	else
	{
		status->exit_status = FAILURE;
		status->return_value = FAILURE;
		ft_putfd("pwd: Unknown error\n", 2);
	}
}
