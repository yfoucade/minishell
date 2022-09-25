/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 02:39:14 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/25 03:38:38 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_valid_length(char *s)
{
	int		i;

	i = 0;
	while (is_blank_chr(s[i]) || s[i] == '-' || s[i] == '+')
		i++;
	if (ft_strnlen(s + i, 20) > 19)
		return (0);
	return (1);
}

long long	ft_exitcode(char *arg, int *valid)
{
	unsigned long long	code;
	int					negative;

	negative = 0;
	code = ft_atoull(arg, &negative);
	if (negative && code > 9223372036854775808ULL)
		*valid = 0;
	else if (!negative && code > 9223372036854775807ULL)
		*valid = 0;
	if (!ft_valid_length(arg))
		*valid = 0;
	if (negative)
		code = -code;
	return (code);
}

void	clean_exit(t_status *status, int exit_code)
{
	free_parsed_command(status);
	free_status(status);
	rl_clear_history();
	exit(exit_code);
}

/**
 * @brief Exit shells
 * No args = last command exit code
 * One arg = arg exit code (must be ll range)
 * Two or more args = error (and no exit)
 * Invalid arg = error (exit code 2)
 * @param status Status structure
 * @return unsigned char Status code
 */
unsigned char	ft_exit(t_status *status)
{
	int			args;
	int			valid;
	long long	code;

	valid = 1;
	args = array_size(status->args);
	if (status->ft_isatty && !status->in_pipe && !status->out_pipe)
		ft_putfd("exit\n", STDERR_FILENO);
	if (args > 2)
	{
		ft_putfd("exit: too many arguments\n", STDERR_FILENO);
		return (FAILURE);
	}
	if (args <= 1)
		clean_exit(status, status->exit_status);
	code = ft_exitcode(status->args[1], &valid);
	if (!valid)
	{
		ft_putfd("exit: non numeric argument\n", STDERR_FILENO);
		code = 2;
	}
	clean_exit(status, code);
	return (SUCCESS);
}
