/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:34:21 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/10 17:02:48 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "resolve_path.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

char	*ft_strchr(char *haystack, char needle)
{
	while (*haystack && *haystack != needle)
		++haystack;
	return (haystack);
}

char	*ft_strcat(char *s1, char *s2)
{
	int	size;
	char	*res;
	char	*tmp;

	size = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(size + 1);
	tmp = res;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (res);
}

char	*ft_strcat_free(char *s1, char *s2, char free_s1, char free_s2)
{
	int		i;
	int		j;
	char	*res;

	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	j = -1;
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = '\0';
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (res);
}

int	ft_strlen(char *str)
{
	int	res;

	res = 0;
	while (*str++)
		++res;
	return (res);
}

void	print_str_list(t_str_list *str_list)
{
	while (str_list)
	{
		DEBUG(str_list->str);
		str_list = str_list->next;
	}
}

char	*ft_strndup(char *str, int n)
{
	char	*res;
	int		i;
	
	res = malloc(n + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < n)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(char *str)
{
	return (ft_strndup(str, ft_strlen(str)));
}

t_str_list	*lst_add_n(t_str_list **lst, char *str, char *end)
{
	t_str_list	*res;
	t_str_list	*tmp;

	res = malloc(sizeof(*res));
	res->str = ft_strndup(str, end - str);
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

t_str_list	*ft_split(char *str, char c)
{
	t_str_list	*res;
	char		*end;

	res = NULL;
	while (*str)
	{
		end = str;
		while (*end && *end != c)
			++end;
		res = lst_add_n(&res, str, end);
		str = end + (*end == c);
	}
	return (res);
}

void	free_lst(t_str_list *lst)
{
	t_str_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->str);
		free(lst);
		lst = tmp;
	}
}