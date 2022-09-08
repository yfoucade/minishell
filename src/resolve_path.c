/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:33:40 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/08 10:23:37 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*relative_path(char *command)
{
	char	*res;

	res = ft_strcat_free(getenv("PWD"), "/", FALSE, FALSE);
	res = ft_strcat_free(res, command, TRUE, FALSE);
	return (res);
}

char	*construct_path(DIR *dirp, char *dirname, struct dirent *direntry)
{
	char	*res;

	res = ft_strcat(dirname, "/");
	res = ft_strcat_free(res, direntry->d_name, TRUE, FALSE);
	closedir(dirp);
	return (res);
}

char	*search_in_directory(char	*dirname, char *target)
{
	char			*res;
	DIR				*dirp;
	struct dirent	*direntry;

	res = NULL;
	dirp = opendir(dirname);
	if (!dirp)
	{
		perror("search_in_directory");
		return (NULL);
	}
	direntry = readdir(dirp);
	while (direntry)
	{
		if (!ft_strcmp(target, direntry->d_name) && direntry->d_type != DT_DIR)
			return (construct_path(dirp, dirname, direntry));
		direntry = readdir(dirp);
	}
	if (errno)
		perror("minishell");
	closedir(dirp);
	return (res);
}

char	*search_paths(t_status *status, char *command)
{
	char		*paths;
	char		*absolute_path;
	t_str_list	*lst_paths;
	t_str_list	*tmp_path;

	absolute_path = NULL;
	paths = ft_getenv(status, "PATH");
	if (!paths)
		return (NULL);
	lst_paths = ft_split(paths, ':');
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

t_command	*resolve_path(t_status *status, char	*command)
{
	t_command	*res;

	res = new_t_command();
	if (!res)
		return (NULL);
	if (*command == '/')
		t_command_set_path(&res, command, FALSE);
	else if (*ft_strchr(command, '/'))
		t_command_set_path(&res, relative_path(command), TRUE);
	else
	{
		if (t_command_set_fun_ptr(&res, search_builtins(command)))
			t_command_set_path(&res, search_paths(status, command), TRUE);
	}
	return (res);
}
