/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 23:42:39 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/10 16:17:00 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

unsigned char	builtin_1(char **args, char **redirections)
{
	printf("Executing builtin_1\n");
	return(0);
}

unsigned char	builtin_2(char **args, char **redirections)
{
	printf("Executing builtin_2\n");
	return(0);
}
