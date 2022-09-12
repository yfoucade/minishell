/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:32:43 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/12 16:20:49 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	lst_add(t_str_list **lst, char *str)
{
	return (lst_add_n(lst, str, str + ft_strlen(str) + 1));
}
