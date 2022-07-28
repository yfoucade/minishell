/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childproc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:30:37 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/28 13:18:31 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILDPROC_H
# define CHILDPROC_H

// -- Access mask (ft_access) --
# define NO_ACCESS 0x0
# define READABLE 0x1
# define WRITEABLE 0x2
# define EXECUTABLE 0x4
# define IS_DIR 0x8
# define EXISTS 0x10

int	ft_access(char *path);

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int		redir_open(char *path, char **argv, char **envp, int fds[]);
int		ft_error(char *command, char *message, int ret);
int		redirect_to_file(char *binary_path, char **args, char **envp, char *output);
int		redirect_append(char *binary_path, char **args, char **envp, char *output);
int		redirect_input(char *command, char *file, char **args, char **envp);
int		redirect_delimiter(char *delim, char *binary, char **args, char **envp);
int		check_binary(char *path);
#endif
