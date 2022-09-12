/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:25:10 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/10 00:10:08 by yfoucade         ###   ########.fr       */
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
	run_shell(&status);
}
