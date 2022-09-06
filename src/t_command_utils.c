/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:44:53 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/06 20:28:30 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_command_set_type(t_command **command, char type)
{
	(*command)->command_type = type;
}

t_command	*new_t_command(void)
{
	t_command	*res;

	res = malloc(sizeof(t_command));
	if (!res)
		return (NULL);
	res->command_type = 0;
	return (res);
}

char	t_command_set_fun_ptr(t_command **command, builtin_ptr fun_ptr)
{
	if (!fun_ptr)
		return (FAILURE);
	(*command)->u_command_ref.fun_ptr = fun_ptr;
	t_command_set_type(command, CMD_BUILTIN);
	return (SUCCESS);
}

char	t_command_set_path(t_command **command, char *path, char free_path)
{
	if (path)
	{
		(*command)->u_command_ref.command_path = ft_strdup(path);
		if (!(*command)->u_command_ref.command_path)
		{
			if (free_path)
				free(path);
			return (FAILURE);
		}
		t_command_set_type(command, CMD_ABS_PATH);
	}
	if (free_path)
		free(path);
	return (SUCCESS);
}

void	t_command_free(t_command **command)
{
	if ((*command)->command_type == CMD_ABS_PATH)
		free((*command)->u_command_ref.command_path);
	free(*command);
}
