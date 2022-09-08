/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_installers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:07:11 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/08 11:07:17 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	install_handlers(t_status *status)
{
	__sighandler_t	ret;

	ret = signal(SIGQUIT, SIG_IGN);
	if (ret == SIG_ERR)
		early_exit();
	if (status->ft_isatty)
	{
		ret = signal(SIGINT, sigint_handler);
		if (ret == SIG_ERR)
			early_exit();
	}
	else
	{
		ret = signal(SIGINT, non_interactive_sigint_handler);
		if (ret == SIG_ERR)
			early_exit();
	}
}

void	waiting_handlers(void)
{
	__sighandler_t	ret;

	ret = signal(SIGQUIT, SIG_IGN);
	if (ret == SIG_ERR)
		exit(1);
	ret = signal(SIGINT, waiting_child);
	if (ret == SIG_ERR)
		exit(1);
}

void	heredoc_handlers(void)
{
	__sighandler_t	ret;

	ret = signal(SIGQUIT, SIG_DFL);
	if (ret == SIG_ERR)
		exit(1);
	ret = signal(SIGINT, SIG_DFL);
	if (ret == SIG_ERR)
		exit(1);
}

void	uninstall_handlers(void)
{
	__sighandler_t	ret;

	ret = signal(SIGINT, SIG_IGN);
	if (ret == SIG_ERR)
		exit(1);
}
