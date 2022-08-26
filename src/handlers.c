/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:07:46 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/26 16:48:47 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	early_exit(void)
{
	perror("minishell");
	exit(1);
}

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return;
}

void	waiting_child(int sig)
{
	(void)sig;
	printf("\n");
}

void	install_handlers(void)
{
	__sighandler_t	ret;

	ret = signal(SIGQUIT, SIG_IGN);
	if (ret == SIG_ERR)
		early_exit();
	ret = signal(SIGINT, sigint_handler);
	if (ret == SIG_ERR)
		early_exit();
	// try invalid handler installation
	// ret = signal(SIGKILL, SIG_IGN);
	// if (ret == SIG_ERR)
	// 	early_exit();
}

void	uninstall_handlers(void)
{
	__sighandler_t	ret;

	ret = signal(SIGQUIT, SIG_IGN);
	if (ret == SIG_ERR)
		exit(1);
	ret = signal(SIGINT, waiting_child);
	if (ret == SIG_ERR)
		exit(1);
}
