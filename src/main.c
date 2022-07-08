/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:25:10 by yfoucade          #+#    #+#             */
/*   Updated: 2022/07/08 12:32:55 by yfoucade         ###   ########.fr       */
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
	// 	early_exit();
}

int	main(void)
{
	t_environ	environ;

	install_handlers();
	init_environ(&environ);
	run_shell(&environ);
	free_environ(&environ);
	rl_clear_history();
	return (0);
}
