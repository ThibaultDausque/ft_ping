#include <ft_ping.h>

int	main(int ac, char **av)
{
	char	*option;
	// char	*host;

	if (ac != 3)
	{
		printf("ft_ping: missing host operand\n");
		exit(0);
	}
	
	option = av[1];
	// host = av[2];
	parse_opt(option);

	return 0;
}
