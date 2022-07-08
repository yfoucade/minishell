/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:50:34 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/08 16:23:05 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../neo_libft/includes/printf.h"

// TODO : Gerer les couleurs si necessaire ($TERM)
int	ft_error(char *command, char *message, int ret)
{
	ft_fprintf(2, "trash : %s : %s\n", command, message);
	return (ret);
}