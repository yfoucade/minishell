/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:23:49 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/08 10:23:56 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_ptr	search_builtins(char *command)
{
	if (!ft_strcmp(command, "pwd"))
		return (&pwd);
	if (!ft_strcmp(command, "cd"))
		return (&cd);
	if (!ft_strcmp(command, "echo"))
		return (&echo);
	if (!ft_strcmp(command, "export"))
		return (&export);
	if (!ft_strcmp(command, "unset"))
		return (&unset);
	if (!ft_strcmp(command, "env"))
		return (&env);
	if (!ft_strcmp(command, "exit"))
		return (&ft_exit);
	return (NULL);
}
