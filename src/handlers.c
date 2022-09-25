/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:07:46 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/25 03:44:55 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	waiting_child(int sig)
{
	(void)sig;
	printf("\n");
}

void	non_interactive_sigint_handler(int sig)
{
	(void)sig;
	g_stop_non_int = TRUE;
}

void	heredoc_handler(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
}
