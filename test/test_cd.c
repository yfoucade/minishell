/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:27:14 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/06 12:10:34 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
int	ft_change_directory(char *target);

int main(void)
{
	char *home = getenv("HOME");

	// Test with existing paths
	printf("%c", ft_change_directory("/tmp") == 0 ? 'p' : 'f');
	printf("%c", ft_change_directory("/tmp/") == 0 ? 'p' : 'f');
	printf("%c", ft_change_directory("/opt") == 0 ? 'p' : 'f');
	printf("%c", ft_change_directory("/home") == 0 ? 'p' : 'f');
	printf("%c", ft_change_directory("/var") == 0 ? 'p' : 'f');
	printf("%c", ft_change_directory("/etc") == 0 ? 'p' : 'f');
	printf("%c", ft_change_directory("/var/log") == 0 ? 'p' : 'f');
	printf("%c", ft_change_directory(home) == 0 ? 'p' : 'f');
	printf("%c", ft_change_directory(".") == 0 ? 'p' : 'f');
	printf("%c", ft_change_directory("../") == 0 ? 'p' : 'f');
	printf("%c", ft_change_directory("/../") == 0 ? 'p' : 'f');
	printf("%c", ft_change_directory("//") == 0 ? 'p' : 'f');

	// Test with non-existing paths
	printf("%c", ft_change_directory("../abcdef") == 0 ? 'f' : 'p');
	printf("%c", ft_change_directory("/a/") == 0 ? 'f' : 'p');
	printf("%c", ft_change_directory("/tmp/var/log") == 0 ? 'f' : 'p');
	printf("%c", ft_change_directory("/sys/bonjour") == 0 ? 'f' : 'p');

	// Test with illegal paths
	printf("%c", ft_change_directory("...") == 0 ? 'f' : 'p');
	printf("%c", ft_change_directory("\0") == 0 ? 'f' : 'p');
	printf("%c", ft_change_directory(0) == 0 ? 'f' : 'p');

	return (0);
}