/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:51:15 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/02 13:51:38 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_line(int fd)
{
	char			*res;
	char			*tmp;
	char			chunk_buf[BUFFER_SIZE + 1];
	int				status;

	res = malloc(sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '\0';
	status = READING;
	while (status == READING)
	{
		status = get_chunk(fd, chunk_buf);
		tmp = ft_strcat(res, chunk_buf);
		free(res);
		if (!tmp)
			return (NULL);
		res = tmp;
	}
	if ((res[0] == '\0') || status == ERROR)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

int	get_chunk(int fd, char *chunk_buf)
{
	int						i;
	int						ret;
	static t_file_buffer	file = {"", 0};

	chunk_buf[0] = '\0';
	if (file.buf[file.current_index] == '\0')
	{
		file.current_index = 0;
		file.buf[0] = '\0';
		ret = read(fd, file.buf, BUFFER_SIZE);
		if (ret < 1)
			return (EOL * (ret == 0) + ERROR * (ret < 0));
		file.buf[ret] = '\0';
	}
	ret = READING;
	i = 0;
	while (file.buf[file.current_index] && file.buf[file.current_index] != '\n')
		chunk_buf[i++] = file.buf[file.current_index++];
	if (file.buf[file.current_index] == '\n')
	{
		ret = EOL;
		chunk_buf[i++] = file.buf[file.current_index++];
	}
	chunk_buf[i] = '\0';
	return (ret);
}
