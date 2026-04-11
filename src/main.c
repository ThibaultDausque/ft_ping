#include <ft_ping.h>

int	main(int ac, char **av)
{
	//char	*option;
	char	*host;

	if (ac < 2)
	{
		printf("ft_ping: missing host operand\n");
		exit(0);
	}
	
	host = av[1];
	// parse_opt(option);
	ft_ping(host);
	
	return 0;
}
