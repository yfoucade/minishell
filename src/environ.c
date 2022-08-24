/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:04:05 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/24 02:03:22 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_size(char **array)
{
	int	res;

	res = 0;
	while (*(array++))
		++res;
	return (res);
}

char	**copy_environ(char **env)
{
	char	**copy;
	char	**tmp_copy;
	char	**tmp_env;

	copy = (char **)malloc(sizeof(*copy) * (array_size(env) + 1));
	if (!copy)
		return (NULL);
	tmp_env = env;
	tmp_copy = copy;
	while (*tmp_env)
	{
		*(tmp_copy++) = ft_strdup(*(tmp_env++));
		if (!*(tmp_copy - 1))
		{
			free_array(copy);
			return (NULL);
		}
	}
	*tmp_copy = NULL;
	return (copy);
}

char	*ft_getenv(t_status *status, char *variable)
{
	char	**env;
	char	*full_start;

	full_start = ft_strcat(variable, "=");
	env = status->environ;
	while (*env)
	{
		if (ft_startswith(full_start, *env))
		{
			free(full_start);
			return (ft_strchr(*env, '=') + 1);
		}
		++env;
	}
	free(full_start);
	return (NULL);
}
