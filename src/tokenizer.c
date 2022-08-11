/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:47:09 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/11 19:33:46 by yfoucade         ###   ########.fr       */
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

void	add_next_token(t_str_list **tokens, char **command)
{
	char	*end;
	t_str_list	*tmp;
	t_str_list	*new_token;

	while (is_blank_chr(**command))
		(*command)++;
	if (!**command)
		return;
	end = find_token_end(*command);
	new_token = malloc(sizeof(new_token));
	new_token->next = NULL;
	// end is the first character that doesn't belong to the token
	new_token->str = ft_strndup(*command, end - *command);
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
}

t_str_list	*tokenize(char	*command)
{
	t_str_list	*res;

	res = NULL;
	while (*command)
	{
		add_next_token(&res, &command);
	}
	return (res);
}
