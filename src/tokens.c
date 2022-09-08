/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:39:46 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/08 11:39:52 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_operator(char *token)
{
	if (!token)
		return (FALSE);
	if (*token == '<' || *token == '>')
		return (TRUE);
	return (FALSE);
}

char	is_word(char *token)
{
	if (!token)
		return (FALSE);
	return (!is_operator(token));
}

// consider receiving a t_str_list** as well, that we set to
// the element causing the error. If return value is 0 (syntax error),
// then the t_str_list** is made to point to the problematic element.
// If return value is 0 and t_str_list** points to NULL, the problematic
// element is the `newline'.
char	is_valid_syntax(t_str_list	*tokens)
{
	while (tokens)
	{
		if (is_operator(tokens->str))
		{
			if (!tokens->next || !is_word(tokens->next->str))
				return (FALSE);
		}
		tokens = tokens->next;
	}
	return (TRUE);
}
