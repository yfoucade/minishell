/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 02:39:14 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/18 22:28:38 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	ft_exit(t_status *status)
{
	int	exit_code;
	int	args;

	exit_code = 0;
	args = array_size(status->args);
	if (status->ft_isatty)
		ft_putfd("exit\n", STDERR_FILENO);
	if (args == 2)
		exit_code = ft_atoi(status->args[1]);
	else if (args > 2)
	{
		ft_putfd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	rl_clear_history();
	free_status(status);
	exit(exit_code);
}
