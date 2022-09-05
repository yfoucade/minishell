/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:40:22 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/05 11:31:57 by yfoucade         ###   ########.fr       */
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
	{
		ft_exit(status);
	}
	status->pipelines = ft_split_unquoted_c(status->input, '\n');
	if (!status->pipelines)
	{
		free_status(status);
		perror("minishell: ");
		exit(0);
	}
	free(status->input);
	status->input = NULL;
	return (SUCCESS);
}