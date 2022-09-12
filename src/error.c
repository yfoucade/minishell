/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:05:36 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/13 00:38:37 by yfoucade         ###   ########.fr       */
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
	printf("minishell: malloc error\n");
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
	if (errno)
		perror("minishell");
	errno = 0;
	if (status && status->error_msg)
	{
		ft_putfd(status->error_msg, STDERR_FILENO);
		if (status->error_msg[ft_strlen(status->error_msg) - 1] != '\n')
			ft_putfd("\n", STDERR_FILENO);
		free(status->error_msg);
		status->error_msg = NULL;
	}
	if (str)
	{
		ft_putfd("minishell: ", STDERR_FILENO);
		ft_putfd(str, STDERR_FILENO);
	}
	// status->return_value = 0; // not here, make sure to put it elsewhere
}
