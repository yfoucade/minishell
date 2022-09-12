/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:48:14 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/12 22:51:54 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	parse_status(t_status *status)
{
	t_str_list	*tokens_copy;

	tokens_copy = status->tokens;
	while (tokens_copy)
	{
		if (is_word(tokens_copy->str))
		{
			if (lst_add(&status->lst_args, tokens_copy->str))
				return (FAILURE);
		}
		else
		{
			if (lst_add(&status->lst_redirections, tokens_copy->str))
				return (FAILURE);
			tokens_copy = tokens_copy->next;
			if (lst_add(&status->lst_redirections, tokens_copy->str))
				return (FAILURE);
		}
		tokens_copy = tokens_copy->next;
	}
	status->args = lst_to_array(status->lst_args);
	status->redirections = lst_to_array(status->lst_redirections);
	return (SUCCESS);
}

unsigned char	parse_curr_command(t_status *status)
{
	status->tokens = tokenize(status->curr_command->str);
	if (!is_valid_syntax(status->tokens))
	{
		set_error_msg(status, "minishell: missing file name\n");
		status->return_value = ERR_FILENAME_MISSING;
		free_str_list(status->tokens);
		status->tokens = NULL;
	}
	parse_status(status);
	if (expand_array_elements(status, status->args))
	{
		printf("minishell: bad substitution\n");
		return (0);
	}
	if (expand_array_elements(status, status->redirections))
	{
		printf("minishell: ambiguous redirect\n");
		return (0);
	}
	status->command = resolve_path(status, status->args[0]);
	return (SUCCESS);
}
