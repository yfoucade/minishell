/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_installers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:07:11 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/22 16:27:20 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	install(t_status *status, int signum, __sighandler_t handler)
{
	if (signal(signum, handler) == SIG_ERR)
		panic(status);
}

void	install_handlers(t_status *status, int caller)
{
	if (caller == PARENT)
	{
		if (status->ft_isatty)
		{
			install(status, SIGINT, parent_handler);
			install(status, SIGQUIT, parent_handler);
		}
		else
		{
			install(status, SIGINT, non_interactive_parent_handler);
			install(status, SIGQUIT, non_interactive_parent_handler);
		}
	}
	else if (caller == CHILD)
	{
		if (status->ft_isatty)
		{
			install(status, SIGINT, child_handler);
			install(status, SIGQUIT, child_handler);
		}
		else
		{
			install(status, SIGINT, non_interactive_child_handler);
			install(status, SIGQUIT, non_interactive_child_handler);
		}
	}
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
	install(status, SIGQUIT, SIG_IGN);
}
