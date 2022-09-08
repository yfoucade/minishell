/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:37:54 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/08 11:46:10 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_valid_quoting(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			str = ft_strchr(str + 1, *str);
			if (!*str)
				return (FALSE);
		}
		++str;
	}
	return (TRUE);
}

char	is_valid_pipeline(t_str_list *commands)
{
	char	*tmp;

	if (!commands)
		return (FALSE);
	while (commands)
	{
		tmp = commands->str;
		while (*tmp == ' ' || *tmp == '\t')
			tmp++;
		if (!*tmp)
			return (FALSE);
		commands = commands->next;
	}
	return (TRUE);
}

void	save_prev_pipeline(t_status *status)
{
	free(status->prev_pipeline);
	status->prev_pipeline = status->curr_pipeline;
	status->curr_pipeline = NULL;
}

void	free_curr_pipeline(t_status *status)
{
	free(status->curr_pipeline);
	status->curr_pipeline = NULL;
}

void	free_pipelines(t_status *status)
{
	free_str_list(status->pipelines);
	status->pipelines = NULL;
}
