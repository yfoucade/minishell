/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:36:47 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/25 15:08:26 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_name(t_status *status, char *str)
{
	char	*name;
	char	*value;

	if (*str == '?')
		return (uctoa(status->exit_status));
	else if (*str == '{')
	{
		name = ft_strndup(str + 1, ft_strlen(str) - 2);
		if (!is_valid_identifier(name))
		{
			free(name);
			status->exit_status = FAILURE;
			set_error_msg(status, "invalid identifier\n");
			return (NULL);
		}
	}
	else
		name = ft_strdup(str);
	value = ft_strdup(ft_getenv(status, name));
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (value);
}
