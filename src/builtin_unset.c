/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:36:11 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/15 03:32:27 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_except_loop(char **old_env, char **new_env, char *ignore)
{
	while (*old_env)
	{
		if (!ft_startswith(ignore, *old_env))
		{
			*new_env = *old_env;
			++new_env;
		}
		else
			free(*old_env);
		++old_env;
	}
	*new_env = NULL;
}

void	copy_except(t_status *status, char *str)
{
	char	*full_start;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (array_size(status->environ)));
	if (!new_env)
	{
		flush_error_msg(NULL, NULL);
		return ;
	}
	full_start = ft_strcat(str, "=");
	copy_except_loop(status->environ, new_env, full_start);
	free(full_start);
	free(status->environ);
	status->environ = new_env;
}

unsigned char	unset(t_status *status)
{
	char	**args;

	args = status->args;
	while (*++args)
	{
		if (!is_valid_identifier(*args) || !ft_getenv(status, *args))
			continue ;
		copy_except(status, *args);
	}
	return (SUCCESS);
}
