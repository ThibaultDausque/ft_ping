#include <ft_ping.h>

int	parse_opt(char *line)
{
	if (strcmp(line, "-v") && strcmp(line, "-?"))
	{
		printf("ft_ping: invalid option -- \'%s\'\n", line);
		exit(0);
	}
	return 0;
}
