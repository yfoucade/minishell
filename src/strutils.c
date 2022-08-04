/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:09:21 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/02 16:02:05 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen(char	*str)
{
	int	res;

	res = 0;
	while (*str++)
		res++;
	return (res);
}

char	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}
char	ft_strchr_chr(char *haystack, char needle)
{
	while (*haystack && *haystack != needle)
		haystack++;
	return (*haystack);
}

char	*ft_strchr(char *haystack, char needle)
{
	while (*haystack && *haystack != needle)
		haystack++;
	return (haystack);
}

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
	while (++i < n)
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
	res = ft_strdup(start, end + 1 - start);
	return (res);
}

char	is_meta(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	if (c == '<' || c == '|' || c == '>')
		return (TRUE);
	return (FALSE);
}

int	count(char *str, char c)
{
	int	res;

	res = 0;
	while (*str)
		res += *str++ == c;
	return (res);
}

t_str_list	*lst_add_n(t_str_list **lst, char *str, char *end)
{
	t_str_list	*res;
	t_str_list	*tmp;

	res = malloc(sizeof(*res));
	res->str = ft_strdup(str, end - str);
	res->next = NULL;
	if (!*lst)
		return (res);
	tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = res;
	return (*lst);
}

t_str_list	*lst_add(t_str_list **lst, char *str)
{
	return (lst_add_n(lst, str, str + ft_strlen(str) + 1));
}

/*
split a string str at each character c that is not between quotes
*/
t_str_list	*ft_split_unquoted_c(char *str, char c)
{
	t_str_list	*res;
	char		*chunk_end;

	if (!str)
		return (NULL);
	if (*str == '|' || str[ft_strlen(str) - 1] == '|')
		return (NULL);
	res = NULL;
	while (*str)
	{
		chunk_end = str;
		while (*chunk_end && *chunk_end != c)
		{
			if (*chunk_end == '"' || *chunk_end == '\'')
				chunk_end = ft_strchr(chunk_end + 1, *chunk_end);
			if (!*chunk_end)
				break;
			chunk_end++;
		} 
		res = lst_add_n(&res, str, chunk_end);
		str = chunk_end + (*chunk_end == c);
	}
	return (res);
}

char	**lst_to_array(t_str_list *lst)
{
	char		**res;
	char		**tmp_arr;
	t_str_list	*tmp_lst;
	int			count;

	tmp_lst = lst;
	count = 0;
	while (tmp_lst)
	{
		++count;
		tmp_lst = tmp_lst->next;
	}
	res = malloc(sizeof(char*) * (count + 1));
	tmp_arr = res;
	tmp_lst = lst;
	while (tmp_lst)
	{
		*tmp_arr++ = ft_strdup(tmp_lst->str, ft_strlen(tmp_lst->str));
		tmp_lst = tmp_lst->next;
	}
	*tmp_arr = NULL;
	return (res);
}