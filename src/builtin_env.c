/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 02:33:12 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/21 12:30:47 by jallerha         ###   ########.fr       */
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
		return (SUCCESS);
	while (env[++i])
	{
		if (ft_strnlen(ft_strchr(env[i], '='), 2) < 2)
			continue;
		if (ft_putfd(env[i], status->out_fd) || ft_putfd("\n", status->out_fd))
			return (FAILURE);
	}
	return (SUCCESS);
}
