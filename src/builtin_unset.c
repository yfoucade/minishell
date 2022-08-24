/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:36:11 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/24 02:32:49 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_exept(t_status *status, char *str)
{
	char	*full_start;
	char	**new_env;
	char	**tmp_old_env;
	char	**tmp_new_env;

	new_env = malloc(sizeof(char *) * (array_size(status->environ)));
	tmp_new_env = new_env;
	tmp_old_env = status->environ;
	full_start = ft_strcat(str, "=");
	while (*tmp_old_env)
	{
		if (!ft_startswith(full_start, *tmp_old_env))
		{
			*tmp_new_env = ft_strdup(*tmp_old_env);
			if (!*tmp_new_env)
			{
				free_array(new_env);
				exit (1);
			}
			++tmp_new_env;
		}
		++tmp_old_env;
	}
	*tmp_new_env = NULL;
	free(full_start);
	free_array(status->environ);
	status->environ = new_env;
}

void	unset(t_status *status)
{
	char	**args;

	args = status->args;
	while (*++args)
	{
		if (!is_valid_identifier(*args) || !ft_getenv(status, *args))
			continue ;
		ft_copy_exept(status, *args);
	}
}
