/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:49:09 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/26 17:02:59 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	replace_env_variable(t_status *status, t_env_variable *env_variable)
{
	char	**env_copy;
	char	*put_in_env;

	env_copy = status->environ;
	while (*env_copy)
	{
		if (ft_startswith(env_variable->name, *env_copy))
			break;
		++env_copy;
	}
	put_in_env = ft_strcat(env_variable->name, "=");
	put_in_env = ft_strcat_free(put_in_env, env_variable->value, TRUE, FALSE);
	free(*env_copy);
	*env_copy = put_in_env;
	return ;
}

void	add_env_variable(t_status *status, t_env_variable *env_variable)
{
	char	**new_env;
	char	**tmp_old_env;
	char	**tmp_new_env;
	char	*put_in_env;

	new_env = malloc(sizeof(char *) * (array_size(status->environ) + 2));
	tmp_new_env = new_env;
	tmp_old_env = status->environ;
	while (*tmp_old_env)
	{
		*(tmp_new_env++) = ft_strdup(*(tmp_old_env++));
		if (!*(tmp_new_env - 1))
		{
			free_array(new_env);
			exit (1);
		}
	}
	put_in_env = ft_strcat(env_variable->name, "=");
	put_in_env = ft_strcat_free(put_in_env, env_variable->value, TRUE, FALSE);
	*(tmp_new_env++) = put_in_env;
	*tmp_new_env = NULL;
	free_array(status->environ);
	status->environ = new_env;
}

void	export(t_status *status)
{
	char	**args;
	t_env_variable	*env_variable;

	args = status->args;
	while (*++args)
	{
		status->exit_status = 0;
		env_variable = parse_env_variable(*args);
		if (!env_variable || !env_variable->name || !env_variable->value)
			exit(1);
		if (!is_valid_identifier(env_variable->name))
		{
			status->exit_status = 1;
			printf("export: `%s': not a valid identifier\n", env_variable->name);
		}
		else if (ft_getenv(status, env_variable->name))
			replace_env_variable(status, env_variable);
		else
			add_env_variable(status, env_variable);
		free(env_variable->name);
		free(env_variable->value);
		free(env_variable);
	}
}