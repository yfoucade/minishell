/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:08:26 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/01 09:33:02 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_status *status)
{
	int	ret;

	ret = array_size(status->args);
	if (ret == 1)
		return ;
	ret = chdir(status->args[1]);
	if (ret == -1)
	{
		status->return_value = errno;
		status->exit_status = errno;
		perror("cd");
	}
}
