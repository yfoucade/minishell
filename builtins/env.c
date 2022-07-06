/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 21:52:46 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/06 14:32:39 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// TODO : Print exported variables

void	ft_putstr(char *s, int endl)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
	if (endl)
		write(1, "\n", 1);
}

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr(envp[i], 1);
		i++;
	}
}
