#include "ft_ping.h"

// parse the address "google.com" "127.0.0.1"
char*	parse_addr(char *addr)
{
	struct addrinfo	hints, *p;
	struct addrinfo	*servinfo;
	int				fd;

	char	ipstr[INET_ADDRSTRLEN];

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(addr, NULL, &hints, &servinfo) != 0)
	{
		perror("Error: getaddrinfo() fatal error\n");
		exit(0);
	}

	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		struct sockaddr_in	*ipv4;
		void				*addr;
		char				*ipver;

		if (p->ai_family == AF_INET)
		{
			ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
			inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
			printf("	%s: %s\n", ipver, ipstr);
		}
	}

	fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if (fd < 0)
	{
		perror("Error: socket() failed\n");
		exit(0);
	}

	printf("socket OK\n");

	

	return "toto";
}