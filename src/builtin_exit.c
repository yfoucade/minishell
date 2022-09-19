/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 02:39:14 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/19 12:40:28 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	clean_exit(t_status *status, int exit_code)
{
	free_status(status);
	rl_clear_history();
	exit(exit_code);
}

unsigned char	ft_exit(t_status *status)
{
	int	exit_code;
	int	args;

	exit_code = 0;
	args = array_size(status->args);
	if (status->ft_isatty)
		ft_putfd("exit\n", STDERR_FILENO);
	if (!status->args)
		clean_exit(status, 0);
	if (args == 1)
		clean_exit(status, 0);
	if (args == 2 && !ft_str_num(status->args[1]))
	{
		ft_putfd("exit: non numeric argument\n", STDERR_FILENO);
		clean_exit(status, 2);
	}
	if (args == 2)
		clean_exit(status, ft_atoi(status->args[1]));
	if (args > 2)
	{
		ft_putfd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
