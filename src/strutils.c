/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:09:21 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/21 16:38:00 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	is_blank_chr(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	// if (c == '\v' || c == '\f' || c == '\r')
	// 	return (TRUE);
	return (FALSE);
}

char	is_blank_str(char *str)
{
	while (*str)
	{
		if (!is_blank_chr(*str++))
			return (FALSE);
	}
	return (TRUE);
}

char	*ft_strdup(char *str, int n)
{
	char	*res;
	int		i;
	
	res = malloc(n + 1);
	i = -1;
	while (++i < n + 1)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

char	*trim(char *str)
{
	char	*res;
	char	*start;
	char	*end;

	start = str;
	while (*start && is_blank_chr(*start))
		start++;
	end = start;
	res = start - 1;
	while (*++res)
	{
		if (!is_blank_chr(*res))
			end = res;
	}
	res = ft_strdup(start, end - start);
	return (res);
}
