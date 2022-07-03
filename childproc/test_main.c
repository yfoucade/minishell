/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:48:11 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/03 22:57:40 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../includes/childproc.h"

int main(int argc, char **argv, char **envp)
{
	int	fds[2];

	if (argc != 2)
		return (1);
	if (strcmp(argv[1], "stdout") == 0)
	{
		fds[0] = 1;
		fds[1] = 2;
	} else {
		fds[0] = open(argv[1], O_WRONLY | O_CREAT, 0644);
		fds[1] = fds[0];
	}
	redir_open("/bin/ls", argv + 1, envp, fds);
	return (0);
}