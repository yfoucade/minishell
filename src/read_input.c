/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:40:22 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/12 12:40:40 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	read_input(t_status *status)
{
	status->input = readline(PS1);
	if (!status->input)
		exit(0);
	status->pipelines = ft_split_unquoted_c(status->input, '\n');
	if (!status->input || !status->pipelines)
	{
		free_status(status);
		perror("minishell: ");
		exit(0);
	}
	return (SUCCESS);
}