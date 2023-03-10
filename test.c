#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	main(int argc, char *argv[])
{
	(void)argv;
	printf("args: %d\n", argc);
	fflush(stdout);
	return (0);
}
