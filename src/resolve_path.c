/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:33:40 by yfoucade          #+#    #+#             */
/*   Updated: 2022/08/24 02:43:33 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

builtin_ptr	search_builtins(char *command)
{
	if (!ft_strcmp(command, "pwd"))
		return (&pwd);
	if (!ft_strcmp(command, "cd"))
		return (&cd);
	if (!ft_strcmp(command, "echo"))
		return (&echo);
	if (!ft_strcmp(command, "export"))
		return (&export);
	if (!ft_strcmp(command, "unset"))
		return (&unset);
	if (!ft_strcmp(command, "env"))
		return (&env);
	if (!ft_strcmp(command, "exit"))
		return (&ft_exit);
	return (NULL);
}

char	*relative_path(char *command)
{
	char	*res;

	res = ft_strcat_free(getenv("PWD"), "/", FALSE, FALSE);
	res = ft_strcat_free(res, command, TRUE, FALSE);
	return (res);
}

char	*search_in_directory(char	*dirname, char *target)
{
	char	*res;
	DIR		*dirp;
	struct dirent	*direntry;

	res = NULL;
	dirp = opendir(dirname);
	if (!dirp)
	{
		perror("search_in_directory: ");
		return (NULL);
	}
	direntry = readdir(dirp);
	while (direntry)
	{
		if (!ft_strcmp(target, direntry->d_name))
		{
			res = ft_strcat_free(dirname, "/", FALSE, FALSE);
			res = ft_strcat_free(res, direntry->d_name, TRUE, FALSE);
			closedir(dirp);
			return (res);
		}
		direntry = readdir(dirp);
	}
	if (errno)
		perror("minishell: ");
	closedir(dirp);
	return (res);
}

char	*search_paths(char *command)
{
	char	*paths;
	char	*absolute_path;
	t_str_list	*lst_paths;
	t_str_list	*tmp_path;

	absolute_path = NULL;
	paths = getenv("PATH");
	if (!paths)
		return (NULL);
	lst_paths = ft_split(paths, ':');
	tmp_path = lst_paths;
	while (tmp_path)
	{
		absolute_path = search_in_directory(tmp_path->str, command);
		if (absolute_path)
			break;
		tmp_path = tmp_path->next;
	}
	free_str_list(lst_paths);
	return (absolute_path);
}

t_command	*resolve_path(char	*command)
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
			t_command_set_path(&res, search_paths(command), TRUE);
	}
	return (res);
}
