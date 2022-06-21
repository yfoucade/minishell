/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:25:10 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/21 13:48:18 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_environ	environ;

	init_environ(&environ);
	run_shell(&environ);
	free_environ(&environ);
	rl_clear_history();
	return (0);
}
