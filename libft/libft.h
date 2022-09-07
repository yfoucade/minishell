/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:01:24 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/07 12:28:45 by yfoucade         ###   ########.fr       */
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
}	t_str_list;

void		free_array(char **array);
void		free_str_list(t_str_list *str_list);
char		ft_is_alnum(char c);
char		ft_is_alpha(char c);
t_str_list	*ft_split_unquoted_c(char *str, char c);
t_str_list	*ft_split(char *str, char c);
char		ft_startswith(char *little, char *big);
char		*ft_strcat_free(char *s1, char *s2, char free_s1, char free_s2);
char		*ft_strcat(char *s1, char *s2);
char		*ft_strchr(char *haystack, char needle);
int			ft_strcmp(char *s1, char *s2);
char		ft_strchr_chr(char *haystack, char needle);
char		*ft_strdup(char *str);
int			ft_strlen(char	*str);
char		*ft_strndup(char *str, int n);
char		is_blank_chr(char c);
char		is_blank_str(char *str);
char		is_meta(char c);
t_str_list	*lst_add_n(t_str_list **lst, char *str, char *end);
t_str_list	*lst_add(t_str_list **lst, char *str);
char		**lst_to_array(t_str_list *lst);
char		*trim(char *str);
char		*uctoa(unsigned char n);

#endif