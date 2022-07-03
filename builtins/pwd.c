/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:06:39 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/03 22:14:53 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

void	ft_putstr(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

void	ft_print_working_directory(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_putstr(path);
		free(path);
		return ;
	}
	if (errno == ENOENT)
		ft_putstr("pwd : No such file or directory");
	else if (errno == EACCES)
		ft_putstr("pwd : Permission denied");
	else if (errno == ENOTDIR)
		ft_putstr("pwd : Not a directory");
	else if (errno == EROFS)
		ft_putstr("pwd : Read-only file system");
	else
		ft_putstr("pwd : Unknown error");
}

int	main(void)
{
	ft_print_working_directory();
	return (0);
}
