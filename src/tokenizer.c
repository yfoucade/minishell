/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:47:09 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/14 21:05:12 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_str_list *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("token %d: |%s|\n", i++, tokens->str);
		tokens = tokens->next;
	}
}

char	*find_token_end(char *command)
{
	if (*command == '<' || *command == '>')
		return (command + (command[1] == *command) + 1);
	while (*command && !is_meta(*command))
	{
		if (*command == '\'' || *command == '"')
			command = ft_strchr(command + 1, *command);
		++command;
	}
	return (command);
}

char	add_next_token(t_str_list **tokens, char **command)
{
	char		*end;
	t_str_list	*tmp;
	t_str_list	*new_token;

	while (is_blank_chr(**command))
		(*command)++;
	if (!**command)
		return (SUCCESS);
	end = find_token_end(*command);
	new_token = malloc(sizeof(*new_token));
	if (!new_token)
		return (FAILURE);
	new_token->next = NULL;
	new_token->str = ft_strndup(*command, end - *command);
	if (!new_token->str)
		return (FAILURE);
	*command = end;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
	return (SUCCESS);
}

char	tokenize(t_status *status, char	*command)
{
	t_str_list	*res;

	res = NULL;
	while (*command)
	{
		if (add_next_token(&res, &command))
		{
			free_str_list(res);
			status->tmp_exit = FAILURE;
			set_error_msg(status, "minishell: error during tokenization\n");
			return (FAILURE);
		}
	}
	status->tokens = res;
	return (SUCCESS);
}
