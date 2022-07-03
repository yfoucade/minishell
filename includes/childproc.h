/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childproc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallerha <jallerha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:30:37 by jallerha          #+#    #+#             */
/*   Updated: 2022/07/03 22:36:40 by jallerha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILDPROC_H
# define CHILDPROC_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	redir_open(char *path, char **argv, char **envp, int fds[]);

#endif