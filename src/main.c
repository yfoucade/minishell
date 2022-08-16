/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:25:10 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/14 15:37:35 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_status	status;

	// print_str_tab(environ);
	install_handlers();
	init_status(&status);
	run_shell(&status);
	free_status(&status);
	rl_clear_history();
	return (0);
}
