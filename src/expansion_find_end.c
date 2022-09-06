/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_find_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:53:36 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/06 21:53:56 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_variable_end(char *s)
{
	char	*closing;

	if (*s == '?')
		return (s + 1);
	if (*s == '_' || ft_is_alpha(*s))
	{
		while (ft_is_alnum(*s) || *s == '_')
			s++;
		return (s);
	}
	if (*s == '{')
	{
		closing = ft_strchr(s + 1, '}');
		if (*closing == '}')
			return (closing + 1);
	}
	return (s);
}

char	*find_constant_end(char *command)
{
	while (*command)
	{
		if (*command == '$')
			return (command);
		++command;
	}
	return (command);
}

char	*find_chunk_end(char *command)
{
	if (*command == '$')
		return (find_variable_end(command + 1));
	else
		return (find_constant_end(command));
}
