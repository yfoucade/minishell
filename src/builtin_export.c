/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:49:09 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/15 03:31:13 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_valid_identifier(char *str)
{
	if (!str || !*str || !(ft_is_alpha(*str) || *str == '_'))
		return (FALSE);
	while (*++str)
	{
		if (!ft_is_alnum(*str) && !(*str == '_'))
			return (FALSE);
	}
	return (TRUE);
}

char	replace_env_variable(t_status *status, char *name, char *value)
{
	char	**env_copy;
	char	*put_in_env;
	char	*full_start;

	env_copy = status->environ;
	full_start = ft_strcat(name, "=");
	if (!full_start)
		return (FAILURE);
	while (*env_copy)
	{
		if (ft_startswith(full_start, *env_copy))
			break ;
		++env_copy;
	}
	free(full_start);
	if (!*env_copy)
		return (FAILURE);
	put_in_env = ft_strcat_free(ft_strcat(name, "="), value, TRUE, FALSE);
	if (!put_in_env)
		return (FAILURE);
	free(*env_copy);
	*env_copy = put_in_env;
	return (SUCCESS);
}

void	copy_array_values(char **old, char **new)
{
	if (!old || !new)
		return ;
	while (*old)
		*(new++) = *(old++);
	*new = NULL;
}

char	add_env_variable(t_status *status, char *name, char *value)
{
	char	**new_env;
	char	**tmp_new_env;
	char	*put_in_env;

	new_env = malloc(sizeof(char *) * (array_size(status->environ) + 2));
	tmp_new_env = new_env;
	copy_array_values(status->environ, tmp_new_env);
	put_in_env = ft_strcat_free(ft_strcat(name, "="), value, TRUE, FALSE);
	if (!new_env || !put_in_env)
	{
		free_array(new_env);
		free(put_in_env);
		return (FAILURE);
	}
	while (*tmp_new_env)
		++tmp_new_env;
	*(tmp_new_env++) = put_in_env;
	*tmp_new_env = NULL;
	free(status->environ);
	status->environ = new_env;
	return (SUCCESS);
}

char	replace_or_add(t_status *status, char *name, char *value)
{
	if (ft_getenv(status, name))
	{
		if (replace_env_variable(status, name, value))
			return (FAILURE);
	}
	else
	{
		if (add_env_variable(status, name, value))
			return (FAILURE);
	}
	return (SUCCESS);
}

unsigned char	export(t_status *status)
{
	char			**args;
	t_env_variable	*env_variable;

	args = status->args;
	while (*++args)
	{
		status->exit_status = 0;
		env_variable = parse_env_variable(*args);
		if (!env_variable)
			continue ;
		if (!is_valid_identifier(env_variable->name))
			printf("export: `%s': not a valid identifier\n", env_variable->name);
		else
			replace_or_add(status, env_variable->name, env_variable->value);
		free(env_variable->name);
		free(env_variable->value);
		free(env_variable);
	}
	return (SUCCESS);
}
