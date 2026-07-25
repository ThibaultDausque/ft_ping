#include "ft_ping.h"

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		perror("Error: you need to put 2 args");
		exit(0);
	}

	parse_addr(av[1]);
	printf("%s\n", av[1]);
	return 0;
}