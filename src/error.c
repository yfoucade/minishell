/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:05:36 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/25 12:55:59 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic(t_status *status)
{
	if (errno)
		perror("minishell");
	else if (status && status->error_msg)
		flush_error_msg(status, NULL);
	else
		ft_putfd("minishell: Fatal error\n", STDERR_FILENO);
	free_status(status);
	exit(1);
}

void	malloc_error(t_status *status)
{
	(void)status;
	ft_putfd("minishell: malloc error\n", STDERR_FILENO);
}

char	set_error_msg(t_status *status, char *str)
{
	free(status->error_msg);
	status->error_msg = ft_strdup(str);
	if (!status->error_msg)
		return (ERR_MALLOC);
	return (SUCCESS);
}

void	flush_error_msg(t_status *status, char *str)
{
	if (status && status->error_msg)
	{
		errno = 0;
		ft_putfd("minishell: ", STDERR_FILENO);
		ft_putfd(status->error_msg, STDERR_FILENO);
		if (status->error_msg[ft_strlen(status->error_msg) - 1] != '\n')
			ft_putfd("\n", STDERR_FILENO);
		free(status->error_msg);
		status->error_msg = NULL;
	}
	else if (errno)
	{
		perror("minishell");
		errno = 0;
	}
	else if (str)
	{
		ft_putfd("minishell: ", STDERR_FILENO);
		ft_putfd(str, STDERR_FILENO);
	}
}

int	ft_cmd_not_found(char *command)
{
	if (!command)
		return (0);
	ft_putfd(command, STDERR_FILENO);
	ft_putfd(": command not found\n", STDERR_FILENO);
	return (127);
}
