/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:39:59 by yfoucade          #+#    #+#             */
/*   Updated: 2022/07/29 17:31:33 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av)
{
	int		fd;
	char	*term_name;
	int		is_term;
	int		orig_output_fd;

	orig_output_fd = dup(STDOUT_FILENO);
	fd = open("tmp",
			  O_RDWR | O_CREAT | O_APPEND,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	is_term = isatty(STDOUT_FILENO);
	if (is_term)
	{
		term_name = ttyname(STDOUT_FILENO);
		printf("ttyname: %s\n", term_name);
	}
	else
	{
		printf("%d is not a tty\n", STDOUT_FILENO);
	}
	dup2(fd, 1);
	printf("coucou\n");
	fflush(stdout);
	close(fd);
	execve("/bin/echo", av, NULL);
	
}
