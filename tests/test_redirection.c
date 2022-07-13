#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av)
{
	int	fd;

	fd = open("tmp",
			  O_RDWR | O_CREAT | O_APPEND,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	dup2(fd, 1);
	printf("coucou\n");
	fflush(stdout);
	execve("/bin/echo", av, NULL);
}
