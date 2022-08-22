/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:32:15 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/22 16:31:07 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	pwd(t_status *status)
{
	char	*absolute_pathname;

	(void)status;
	absolute_pathname = getcwd(NULL, 0);
	printf("%s\n", absolute_pathname);
	free(absolute_pathname);
	return (0);
}

unsigned char	cd(t_status *status)
{
	int	ret;

	ret = chdir(status->args[1]);
	return (ret);
}
