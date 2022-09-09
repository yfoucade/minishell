/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 02:33:12 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/09 17:40:43 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_status *status)
{
	char	**env;

	env = status->environ;
	// todo: add sanity check
	while (*env)
	{
		ft_putfd(*env++, status->out_fd);
		ft_putfd("\n", status->out_fd);
	}
}
