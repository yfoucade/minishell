/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:48:14 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/08 11:50:54 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	parse(t_str_list *tokens, t_str_list **args, t_str_list **redirections)
{
	*args = NULL;
	*redirections = NULL;
	while (tokens)
	{
		//todo: check failure after each update
		if (is_word(tokens->str))
			*args = lst_add(args, tokens->str);
		else
		{
			*redirections = lst_add(redirections, tokens->str);
			tokens = tokens->next;
			*redirections = lst_add(redirections, tokens->str);
		}
		tokens = tokens->next;
	}
	return (SUCCESS);
}

char	parse_status(t_status *status)
{
	t_str_list	*tokens_copy;

	tokens_copy = status->tokens;
	while (tokens_copy)
	{
		//todo: check failure after each update
		if (is_word(tokens_copy->str))
			status->lst_args = lst_add(&status->lst_args, tokens_copy->str);
		else
		{
			status->lst_redirections = lst_add(
					&status->lst_redirections, tokens_copy->str);
			tokens_copy = tokens_copy->next;
			status->lst_redirections = lst_add(
					&status->lst_redirections, tokens_copy->str);
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
	// do not set error messages here. Instead, pass a flag to tell whether
	// to check for ambiguous redirects or not
	// (always look for bad substitution).
	// return value should tell which error happened. values in 'status' should
	// be set within the function expand_array_elements().
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
