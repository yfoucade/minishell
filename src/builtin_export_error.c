/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:05:55 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/25 14:06:02 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_invalid_identifier(char *identifier)
{
	char			*err_msg;

	err_msg = ft_strcat_free(
			"export: `",
			ft_strcat(
				identifier,
				"': not a valid identifier\n"),
			FALSE,
			TRUE);
	flush_error_msg(NULL, err_msg);
	free(err_msg);
}
