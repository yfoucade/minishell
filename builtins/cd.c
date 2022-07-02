/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bacon <bacon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:14:44 by bacon             #+#    #+#             */
/*   Updated: 2022/07/02 02:01:35 by bacon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

// TODO: Remplacer argv par une liste de tokens (ou autre)
int	ft_change_directory(char **argv)
{
	int		err;

	err = chdir(argv[1]);
	if (err != -1)
		return (0);
	if (errno == EACCES)
		puts("cd : Permission denied");
	else if (errno == ENOENT)
		puts("cd : No such file or directory");
	else if (errno == ENOTDIR)
		puts("cd : Cannot cd into a file");
	else if (errno == EROFS)
		puts("cd : Read-only file system");
	else
		puts("cd : Unknown error");
	return (1);
}

// NOTE: argv[1] est le chemin dans lequel aller, argv[2] permet simplement
// de print le nouveau cwd pour les tests.
int	main(int argc, char **argv)
{
	char	*cwd;
	int		ret;

	ret = 0;
	if (argc >= 2)
		ret = ft_change_directory(argv);
	else
		return (-1);
	if (argc > 2)
	{
		cwd = getcwd(NULL, 0);
		printf("%s", cwd);
	}
	return (ret);
}
