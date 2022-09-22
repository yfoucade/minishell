/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:07:46 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/22 16:35:07 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_handler(int sig)
{
	(void)sig;
	ft_putfd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

// rl_on_new_line() and rl_redisplay() are not used for child handler
// as on SIGQUIT it causes issues with the prompt (double prompt,
// or user can overwrite the prompt, etc.)
void	child_handler(int sig)
{
	(void)sig;
	ft_putfd("\n", STDERR_FILENO);
	rl_replace_line("", 0);
	return ;
}

void	waiting_child(int sig)
{
	(void)sig;
	printf("\n");
}

void	non_interactive_parent_handler(int sig)
{
	(void)sig;
	g_stop_non_int = TRUE;
}

void	non_interactive_child_handler(int sig)
{
	(void)sig;
	g_stop_non_int = TRUE;
}
