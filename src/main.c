/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:25:10 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/22 16:26:34 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	g_stop_non_int;

int	main(int ac, char **av, char **env)
{
	t_status	status;

	(void)ac, (void)av;
	g_stop_non_int = FALSE;
	init_status(&status, env);
	install_handlers(&status, PARENT);
	run_shell(&status);
}
