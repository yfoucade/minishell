/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:33:40 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/19 12:17:03 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*relative_path(t_status *status, char *command)
{
	char	*res;

	res = ft_strcat_free(ft_getenv(status, "PWD"), "/", FALSE, FALSE);
	res = ft_strcat_free(res, command, TRUE, FALSE);
	return (res);
}

char	*construct_path(DIR *dirp, char *dirname, struct dirent *direntry)
{
	char	*res;

	res = ft_strcat(dirname, "/");
	res = ft_strcat_free(res, direntry->d_name, TRUE, FALSE);
	closedir(dirp);
	errno = 0;
	return (res);
}

char	*search_in_directory(char	*dirname, char *target)
{
	DIR				*dirp;
	struct dirent	*direntry;

	dirp = opendir(dirname);
	if (!dirp)
	{
		errno = 0;
		return (NULL);
	}
	direntry = readdir(dirp);
	while (direntry)
	{
		if (!ft_strcmp(target, direntry->d_name) && direntry->d_type != DT_DIR)
			return (construct_path(dirp, dirname, direntry));
		direntry = readdir(dirp);
	}
	closedir(dirp);
	errno = 0;
	return (NULL);
}

char	*search_paths(t_status *status, char *command)
{
	char		*paths;
	char		*absolute_path;
	t_str_list	*lst_paths;
	t_str_list	*tmp_path;

	absolute_path = NULL;
	paths = ft_getenv(status, "PATH");
	lst_paths = ft_split(paths, ':');
	if (!paths || !lst_paths)
		return (free(paths), free_str_list(lst_paths), NULL);
	tmp_path = lst_paths;
	while (tmp_path)
	{
		absolute_path = search_in_directory(tmp_path->str, command);
		if (absolute_path)
			break ;
		tmp_path = tmp_path->next;
	}
	free_str_list(lst_paths);
	return (absolute_path);
}

t_command	*resolve_path(t_status *status, char *command)
{
	t_command	*res;

	res = new_t_command();
	if (!res || !command || !*command)
		return (NULL);
	if (*command == '/')
	{
		if (t_command_set_path(&res, command, FALSE))
			return (free(res), NULL);
	}
	else if (*ft_strchr(command, '/'))
	{
		if (t_command_set_path(&res, relative_path(status, command), TRUE))
			return (free(res), NULL);
	}
	else
	{
		if (t_command_set_fun_ptr(&res, search_builtins(command)))
		{
			if (t_command_set_path(&res, search_paths(status, command), TRUE))
				return (free(res), NULL);
		}
	}
	return (res);
}
