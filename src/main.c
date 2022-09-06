/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:25:10 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/06 18:23:38 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	g_stop_non_int;

int	main(void)
{
	t_status	status;

	g_stop_non_int = FALSE;
	init_status(&status);
	install_handlers(&status);
	status.environ = copy_environ(environ);
	add_custom_variables(&status);
	run_shell(&status);
	free_status(&status);
	free_array(environ);
	rl_clear_history();
	return (0);
}
