/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:53:22 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/06 22:12:55 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../neo_libft/includes/string.h"
#include "../neo_libft/includes/put.h"
#include "../neo_libft/includes/printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PROMPT_MAX 256
#define CWD_MAX_LENGTH 184

int	print_hostname(void)
{
	int		fd;
	int		i;
	char	hostname[32];

	i = 0;
	ft_bzero(hostname, 32);
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (0);
	if (read(fd, hostname, 31) == -1)
	{
		close(fd);
		return (0);
	}
	while (hostname[i++])
	{
		if (hostname[i] == '\n')
		{
			hostname[i] = '\0';
			break ;
		}
	}
	hostname[32] = '\0';
	close(fd);
	ft_putstr_fd(hostname, STDOUT_FILENO);
}

void	prefix_home(char *cwd, int *offset)
{
	char	*home;

	home = getenv("HOME");
	if (home == NULL)
		return ;
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		*(offset) = ft_strlen(home);
		ft_putstr_fd("~", STDOUT_FILENO);
	}
	ft_putstr_fd("~", STDOUT_FILENO);
}

char	*shorten_cwd(char *s, int must_free)
{
	char	*output;
	int		i;

	output = (char *) malloc(sizeof(char) * CWD_MAX_LENGTH);
	if (output == NULL)
		return ("?");
	i = 0;
	ft_bzero(output, CWD_MAX_LENGTH);
	prefix_home(s, &i);
	while (s[i++])
	{
		if (s[i - 1] != '/')
			continue ;
		if (ft_strchr(s + i, '/') == NULL)
		{
			ft_putchar_fd('/', STDOUT_FILENO);
			ft_strcat(output, s + i);
			if (must_free)
				free(s);
			break ;
		}
		ft_putchar_fd('/', STDOUT_FILENO);
		ft_putchar_fd(s[i], STDOUT_FILENO);
	}	
	return (output);
}

void	print_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		ft_putchar_fd('?', STDOUT_FILENO);
	if (ft_strlen(cwd) >= 31)
	{
		cwd = shorten_cwd(cwd, 1);
		ft_putstr_fd(cwd, STDOUT_FILENO);
	}
	free(cwd);
}

void	display_prompt(void)
{
	char	*cwd;
	char	output[256];
	char	*hostname;
	int		must_free;

	ft_printf("%s@", getenv("USER"));
	if (!print_hostname())
		ft_putstr_fd("?", STDOUT_FILENO);
	ft_putstr_fd(":", STDOUT_FILENO);
	print_cwd();
	ft_putstr_fd("$ ", STDOUT_FILENO);
}
