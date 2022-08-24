/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:11:22 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/23 23:36:54 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_flag(char *s)
{
	if (*s++ != '-')
		return (FALSE);
	if (!*s)
		return (FALSE);
	while (*s)
		if (*s++ != 'n')
			return (FALSE);
	return (TRUE);
}

void	echo(t_status *status)
{
	char	print_newline;
	char	prefix_whitespace;
	char	**args;

	print_newline = TRUE;
	prefix_whitespace = FALSE;
	args = status->args;
	while (*++args)
	{
		if (ft_is_flag(*args))
			print_newline = FALSE;
		else
		{
			if (prefix_whitespace)
				ft_putstr(" ");
			prefix_whitespace = TRUE;
			ft_putstr(*args);
		}
	}
	if (print_newline)
		ft_putstr("\n");
	return ;
}
