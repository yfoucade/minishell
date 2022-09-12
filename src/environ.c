/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:04:05 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/10 11:56:16 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_size(char **array)
{
	int	res;

	if (!array)
		return (0);
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
		panic(NULL);
	tmp_env = env;
	tmp_copy = copy;
	while (*tmp_env)
	{
		*(tmp_copy++) = ft_strdup(*(tmp_env++));
		if (!*(tmp_copy - 1))
		{
			free_array(copy);
			panic(NULL);
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
	if (!full_start)
		return (NULL);
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

char	add_custom_variables(t_status *status)
{
	if (replace_or_add(status, "PS1", "$ "))
		return (FAILURE);
	if (replace_or_add(status, "PS2", "> "))
		return (FAILURE);
	return (SUCCESS);
}

t_env_variable	*parse_env_variable(char *str)
{
	t_env_variable	*res;
	char			*equal_sign;

	res = malloc(sizeof(t_env_variable));
	if (!res)
		return (NULL);
	equal_sign = ft_strchr(str, '=');
	res->name = ft_strndup(str, equal_sign - str);
	res->value = ft_strdup(equal_sign + (*equal_sign == '='));
	if (!res->name || !res->value)
	{
		free(res->name);
		free(res->value);
		free(res);
		return (NULL);
	}
	return (res);
}
