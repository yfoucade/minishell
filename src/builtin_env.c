/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 02:33:12 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/24 15:00:23 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_status *status)
{
	char	**env;

	env = status->environ;
	while (*env)
	{
		ft_putfd(*env++, status->out_fd);
		ft_putfd("\n", status->out_fd);
	}
}
