/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:47:09 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/23 11:47:19 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("token %d: |%s|\n", i++, tokens->token);
		tokens = tokens->next;
	}
}

char	*find_token_end(char *command)
{
	char	*closing_quote;

	if (is_blank_chr(*command))
		return (command + 1);
	if (*command == '<' || *command == '>')
		return (command + (command[1] == *command) + 1);
	if (*command == '|')
		return (command + (command[1] == *command) + 1);
	if (*command == '\'' || *command == '"')
	{
		closing_quote = ft_strchr(command + 1, *command);
		if (*closing_quote == *command)
			return (closing_quote + 1);
	}
	while (*command && !is_meta_except_dollar(command))
		command++;
	return (command);
}

void	add_next_token(t_token **tokens, char **command)
{
	char	*end;
	t_token	*tmp;
	t_token	*new_token;

	while (is_blank_chr(**command))
		(*command)++;
	end = find_token_end(*command);
	new_token = malloc(sizeof(new_token));
	new_token->next = NULL;
	// end is the first character that doesn't belong to the token
	new_token->token = ft_strdup(*command, end - *command);
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

t_token	*tokenize(char	*command)
{
	t_token	*res;

	res = (t_token*)malloc(sizeof(res));
	res = NULL;
	while (*command)
	{
		add_next_token(&res, &command);
		// printf("tokenize: token added, remaining: |%s|\n", command);
	}
	return (res);
}
