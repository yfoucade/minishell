/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:36:47 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/15 00:48:57 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_name(t_status *status, char *str)
{
	int		len;
	char	*name;
	char	*value;

	len = ft_strlen(str);
	if (*str == '?')
		return (uctoa(status->exit_status));
	else if (*str == '{')
	{
		name = ft_strndup(str + 1, len - 2);
		if (!is_valid_identifier(name))
		{
			free(name);
			status->tmp_exit = FAILURE;
			set_error_msg(status, "minishell: invalid identifier\n");
			return (NULL);
		}
	}
	else
		name = ft_strdup(str);
	value = ft_strdup(ft_getenv(status, name));
	free(name);
	return (value);
}
