/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 02:33:12 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/15 02:35:24 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	env(t_status *status)
{
	char	**env;

	env = status->environ;
	if (!env)
		return (SUCCESS);
	while (*env)
	{
		if (ft_putfd(*env++, status->out_fd) || ft_putfd("\n", status->out_fd))
			return (FAILURE);
	}
	return (SUCCESS);
}
