/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:49:50 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/12 16:15:16 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_str_tab(char **str_tab)
{
	while (*str_tab)
	{
		printf("%s\n", *str_tab);
		++str_tab;
	}
}

char	ft_putfd(char *str, int fd)
{
	if (write(fd, str, ft_strlen(str)) == -1)
	{
		perror("minishell");
		errno = 0;
		return (FAILURE);
	}
	return (SUCCESS);
}

char	ft_putstr(char *str)
{
	return (ft_putfd(str, STDOUT_FILENO));
}
