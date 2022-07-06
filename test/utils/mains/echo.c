#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_echo(char **argv);

char **create_args(char array[6][10])
{
	char **args;
	int i;

	i = 0;
	args = (char **)malloc(sizeof(char *) * 6);
	while (i < 6)
	{
		args[i] = (char *)malloc(sizeof(char) * 10);
		strcpy(args[i], array[i]);
		i++;
	}
	return (args);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int test_no = atoi(argv[1]);
	// With new lines

	switch (test_no)
	{
	case 1:
		char test1[6][10] = {"foo", "bar", "bletch", "baz", "a", "b"};
		ft_echo(create_args(test1));
		break;
	case 2:
		char test2[6][10] = {"mars", "venus", "earth", "saturn", "a", "b"};
		ft_echo(create_args(test2));
		break;
	case 3:
		char test3[6][10] = {"moon", "moon", "sun", "sun", "a", "b"};
		ft_echo(create_args(test3));
		break;
	case 4:
		char test4[6][10] = {"abcdef", "abcdef", "abcdef", "abcdef", "a", "b"};
		ft_echo(create_args(test4));
		break;
	case 5:
		char test5[6][10] = {"0123456", "0123456", "0123456", "0123456", "a", "b"};
		ft_echo(create_args(test5));
		break;
	case 6:
		char test6[6][10] = {"salut", " ", " ", "ciao", "a", "b"};
		ft_echo(create_args(test6));
		break;
	case 7:
		char test7[6][10] = {"foo", "bar", "bletch", "baz", "a", "b"};
		ft_echo(create_args(test7));
		break;
	case 8:
		char test8[6][10]  = {"-n", "foo", "bar", "bletch", "baz", "b"};
		ft_echo(create_args(test8));
		break;
	case 9:
		char test9[6][10]  = {"-n", "mars", "venus", "earth", "saturn", "b"};
		ft_echo(create_args(test9));
		break;
	case 10:
		char test10[6][10] = {"-n", "moon", "moon", "sun", "sun", "b"};
		ft_echo(create_args(test10));
		break;
	case 11:
		char test11[6][10] = {"-n", "abcdef", "abcdef", "abcdef", "abcdef", "b"};
		ft_echo(create_args(test11));
		break;
	case 12:
		char test12[6][10] = {"-n", "0123456", "0123456", "0123456", "0123456", "b"};
		ft_echo(create_args(test12));
		break;
	case 13:
		char test13[6][10] = {"-n", "-nnnnnn", "0123456", "0123456", "0123456", "b"};
		ft_echo(create_args(test13));
		break;
	case 14:
		char test14[6][10] = {"-nnnnnn", "0123456", "0123456", "0123456", "0123456", "b"};
		ft_echo(create_args(test14));
		break;
	default:
		break;
	}
	return (0);
}
