/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:48:14 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/19 12:17:27 by yfoucade         ###   ########.fr       */
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
	if (!status->args || !status->redirections)
		return (FAILURE);
	return (SUCCESS);
}

char	parse_curr_command(t_status *status)
{
	if (tokenize(status, status->curr_command->str))
		return (FAILURE);
	if (!is_valid_syntax(status->tokens))
	{
		set_error_msg(status, "minishell: missing file name or delimiter\n");
		status->tmp_exit = FAILURE;
		return (FAILURE);
	}
	if (parse_status(status))
		return (FAILURE);
	if (expand_array_elements(status, status->redirections))
	{
		set_error_msg(status, "minishell: bad substitution\n");
		status->tmp_exit = FAILURE;
		return (FAILURE);
	}
	if (expand_array_elements(status, status->args))
	{
		set_error_msg(status, "minishell: bad substitution\n");
		status->tmp_exit = FAILURE;
		return (FAILURE);
	}
	status->command = resolve_path(status, status->args[0]);
	return (SUCCESS);
}
