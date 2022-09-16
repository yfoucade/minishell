/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:25:10 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/16 14:48:25 by yfoucade         ###   ########.fr       */
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
	install_handlers(&status);
	run_shell(&status);
}
