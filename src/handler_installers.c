/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_installers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:07:11 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/09 15:51:53 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	install(t_status *status, int signum, __sighandler_t handler)
{
	if (signal(signum, handler) == SIG_ERR)
		panic(status);
}

void	install_handlers(t_status *status)
{
	install(status, SIGQUIT, SIG_IGN);
	if (status->ft_isatty)
		install(status, SIGINT, sigint_handler);
	else
		install(status, SIGINT, non_interactive_sigint_handler);
}

void	waiting_handlers(t_status *status)
{
	install(status, SIGINT, waiting_child);
}

void	heredoc_handlers(t_status *status)
{
	install(status, SIGQUIT, SIG_DFL);
	install(status, SIGINT, SIG_DFL);
}

void	uninstall_handlers(t_status *status)
{
	install(status, SIGINT, SIG_IGN);
}
