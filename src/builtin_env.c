/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 02:33:12 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/27 13:23:47 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	env(t_status *status)
{
	char	**env;
	int		i;

	i = -1;
	env = status->environ;
	if (!env)
	{
		status->hide_empty = TRUE;
		return (SUCCESS);
	}
	while (env[++i])
	{
		if (ft_strnlen(ft_strchr(env[i], '='), 2) < 2 && status->hide_empty)
			continue ;
		if (ft_putfd(env[i], status->out_fd) || ft_putfd("\n", status->out_fd))
		{
			status->hide_empty = TRUE;
			return (FAILURE);
		}
	}
	status->hide_empty = TRUE;
	return (SUCCESS);
}
