/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:54:49 by yfoucade          #+#    #+#             */
/*   Updated: 2022/06/23 13:00:31 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

char	is_variable(char *command)
{
	if (*command++ != '$')
		return (FALSE);
	if (is_blank_chr(*command) || !*command)
		return (FALSE);
	if (is_meta_except_dollar(*command) || *command == '$')
		return (FALSE);
	return (TRUE);
}

char	*find_chunk_end(char *command)
{
	if (is_variable(*command))
		return (find_variable_end(*command));
	else
		return (find_constant_end(*command));
}

void	add_next_chunk(t_token **chunks, char **command)
{
	char	*end;
	t_token	*tmp;
	t_token	*new_chunk;

	end = find_chunk_end(*command);
	new_chunk = malloc(sizeof(new_chunk));
	new_chunk->next = NULL;
	new_chunk->token = ft_strdup(*command, end - *command);
	*command = end;
	if (!*chunks)
		*chunks = new_chunk;
	else
	{
		tmp = *chunks;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_chunk;
	}
}

t_token	*construct_raw_linked_list(char *command)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	res = NULL;
	while (*command)
	{
		add_next_chunk(&res, &command);
	}
	return (res);
}

char	*expand(char *command)
{
	t_token	*chunks;
	char	*res;

	chunks = construct_raw_linked_list(command);
	chunks = substitute(chunks);
	res = concatenate(chunks);
	//free_tokens(chunks);
	return (res);
}