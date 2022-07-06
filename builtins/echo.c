/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 20:41:52 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/06 14:49:48 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_is_flag(char *s)
{
	int	i;

	i = 0;
	if (s[i++] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *s)
{
	int	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

void	ft_putstr(char *s, int space)
{
	write(1, s, ft_strlen(s));
	if (space)
		write(1, " ", 1);
}

void	ft_echo(char **argv)
{
	short int	is_string;
	int			i;

	is_string = 0;
	i = -1;
	while (argv[++i])
	{
		if ((is_string & 0x1) == 0)
		{
			if (ft_is_flag(argv[i]))
				is_string |= 0x2;
			else
			{
				is_string |= 0x1;
				i--;
			}
		}
		else if (is_string & 0x1)
			ft_putstr(argv[i], argv[i + 1] != 0);
	}
	if (is_string == 1)
		ft_putstr("\n", 0);
}
