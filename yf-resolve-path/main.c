/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:03:30 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/10 17:06:10 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "resolve_path.h"

int	main(int ac, char **av)
{
	t_command	*command;

	if (ac < 2)
	{
		fprintf(stderr, "%s\n", "Usage: resolve_path program arguments");
		exit(1);
	}
	command = resolve_path(av[1]);
	if (command->command_type == CMD_BUILTIN)
	{
		command->u_command_ref.fun_ptr(NULL, NULL);
	}
	else if (command->command_type == CMD_ABS_PATH)
		execve(command->u_command_ref.command_path, &av[1], environ);
	else
		printf("Command `%s' not found\n", av[1]);
	t_command_free(&command);
	exit(0);
}
