/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_installers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:07:11 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/09 14:58:40 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	install_handlers(t_status *status)
{
	char	istty;

	istty = status->ft_isatty;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		early_exit();
	if (istty && (signal(SIGINT, sigint_handler) == SIG_ERR))
		early_exit();
	if (!istty && signal(SIGINT, non_interactive_sigint_handler) == SIG_ERR)
		early_exit();
}

void	waiting_handlers(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		early_exit();
	if (signal(SIGINT, waiting_child) == SIG_ERR)
		early_exit();
}

void	heredoc_handlers(void)
{
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		early_exit();
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		early_exit();
}

void	uninstall_handlers(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		early_exit();
}
