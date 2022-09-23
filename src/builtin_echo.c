/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:11:22 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/21 12:47:34 by jallerha         ###   ########.fr       */
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

unsigned char	echo(t_status *status)
{
	char	print_newline;
	char	prefix_whitespace;
	char	**args;
	int		skip_flags;

	skip_flags = 0;
	print_newline = TRUE;
	prefix_whitespace = FALSE;
	args = status->args;
	while (*++args)
	{
		if (ft_is_flag(*args) && !skip_flags)
			print_newline = FALSE;
		else
		{
			if (prefix_whitespace)
				ft_putfd(" ", status->out_fd);
			prefix_whitespace = TRUE;
			ft_putfd(*args, status->out_fd);
			skip_flags = 1;
		}
	}
	if (print_newline)
		ft_putfd("\n", status->out_fd);
	return (SUCCESS);
}
