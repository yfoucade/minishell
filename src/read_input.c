/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:40:22 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/12 23:07:33 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	read_input(t_status *status)
{
	if (status->ft_isatty)
		status->input = readline(ft_getenv(status, "PS1"));
	else
		status->input = get_next_line(STDIN_FILENO);
	if (!status->input)
		ft_exit(status);
	status->pipelines = ft_split_unquoted_c(status->input, '\n');
	free(status->input);
	status->input = NULL;
	if (!status->pipelines)
	{
		flush_error_msg(status, "Could not interpret pipeline\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
