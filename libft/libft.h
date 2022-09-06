/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:01:24 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/06 17:48:02 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
// # include <stddef.h>

# define FALSE 0
# define TRUE 1
typedef struct s_str_list
{
	char				*str;
	struct s_str_list	*next;
} t_str_list;

char	ft_is_alpha(char c);
char	*ft_strcat(char *s1, char *s2);
char	*ft_strchr(char *haystack, char needle);
char	ft_strchr_chr(char *haystack, char needle);
char	*ft_strdup(char *str);
int		ft_strlen(char	*str);
char	*ft_strndup(char *str, int n);
char	is_blank_chr(char c);
t_str_list	*lst_add_n(t_str_list **lst, char *str, char *end);

#endif