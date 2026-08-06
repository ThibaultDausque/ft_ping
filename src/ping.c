#include "ft_ping.h"

long addr_to_dec(char *addr)
{
	int			i = 0;
	int			j = 0;
	long		res;
	long		addr_p;
	int			b = 24;

	while (addr[i])
	{
		while (addr[j] != '.' && addr[j])
			j++;
		addr_p = atoi(ft_substr(addr, i, j++));
		res = res | addr_p << b;
		b -= 8;
		i = j;
	}
	return res;
}

// int ft_checksum(struct ip_t *ip)
// {

// }

// parse the address "google.com" "127.0.0.1"
int	parse_addr(char *addr)
{
	struct addrinfo		hints, *p;
	struct addrinfo		*servinfo;
	struct ip_t 		ip;
	struct icmp_t		*icmp;
	struct sockaddr_in	to;
	int					fd;
	long				addr_dec;
	char				ipstr[INET_ADDRSTRLEN];
	u_char				outpack[MAXPACKET];

	icmp = (struct icmp_t *)outpack;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(addr, NULL, &hints, &servinfo) != 0)
	{
		perror("Error: getaddrinfo() fatal error\n");
		exit(0);
	}

	char	*ipver;
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		struct sockaddr_in	*ipv4;
		
		if (p->ai_family == AF_INET)
		{
			ipv4 = (struct sockaddr_in *)p->ai_addr;
			ipver = "IPv4";
			inet_ntop(AF_INET, &(ipv4->sin_addr), ipstr, INET_ADDRSTRLEN);
			printf("	%s: %s\n", ipver, ipstr);
			break ;
		}
	}

	fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd < 0)
	{
		perror("Error: socket() failed\n");
		exit(0);
	}

	printf("socket OK -> %d\n", fd);

	addr_dec = addr_to_dec(addr);
	printf("	%s -> %ld\n", addr, addr_dec);

	//int		ip_hdr = ip.ip_ihl << 2;

	// ip header
	ip.ip_v = 4;
	ip.ip_tos = 0;
	//ip.ip_length = TL;
	ip.ip_ttl  = TTL;
	ip.ip_p = ICMP;
	ip.ip_cksum = 0;
	ip.ip_saddr = htonl(S_ADDR);
	ip.ip_daddr = htonl(S_ADDR);

	// icmp header
	icmp->icmp_type = 0;
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_id = htons(getpid());
	icmp->icmp_sn = htons(1);
	icmp->icmp_ctt = 0;

	// destination
	bzero((char *)&to, sizeof(to));
	to.sin_family = AF_INET;
	to.sin_addr.s_addr = inet_addr(ipstr);

	unsigned int	h_size = 64;

	if (sendto(fd, &ip, h_size, 0, (struct sockaddr*)&to, sizeof(to)) < 0)
	{
		perror("Error");
		exit(0);
	}

	printf("ICMP packet sent\n");

	u_char	packet[MAXPACKET];
	struct sockaddr_in	src_addr;
	socklen_t	len = sizeof(src_addr);
	if (recvfrom(fd, packet, sizeof(packet), 0, (struct sockaddr*)&src_addr, &len) < 0)
	{
		perror("Error: recvfrom()");
		exit(0);
	}

	printf("ICMP packet received\n");

	return 1;
}