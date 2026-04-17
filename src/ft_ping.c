#include <ft_ping.h>

// OUTPUT EXEMPLE ping -v localhost
// PING localhost (127.0.0.1): 56 data bytes, id 0xac70 = 44144
// 64 bytes from 127.0.0.1: icmp_seq=0 ttl=64 time=0.143 ms
// 64 bytes from 127.0.0.1: icmp_seq=1 ttl=64 time=0.268 ms
// 64 bytes from 127.0.0.1: icmp_seq=2 ttl=64 time=0.294 ms
// 64 bytes from 127.0.0.1: icmp_seq=3 ttl=64 time=0.271 ms
// 64 bytes from 127.0.0.1: icmp_seq=4 ttl=64 time=0.294 ms
// 64 bytes from 127.0.0.1: icmp_seq=5 ttl=64 time=0.291 ms
// 64 bytes from 127.0.0.1: icmp_seq=6 ttl=64 time=0.304 ms
// 64 bytes from 127.0.0.1: icmp_seq=7 ttl=64 time=0.279 ms
// 64 bytes from 127.0.0.1: icmp_seq=8 ttl=64 time=0.281 ms
// 64 bytes from 127.0.0.1: icmp_seq=9 ttl=64 time=0.314 ms
// --- localhost ping statistics ---

//OUTPUT EXEMPLE ping google.com
//Request timeout for icmp_seq 0
// 92 bytes from 10.205.17.254: Destination Port Unreachable
// Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst
//  4  5  00 5400 a558   0 0000  3f  01 039e 10.205.17.29  142.251.39.206
//
// Request timeout for icmp_seq 1
// 92 bytes from 10.205.17.254: Destination Port Unreachable
// Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst
//  4  5  00 5400 205a   0 0000  3f  01 889c 10.205.17.29  142.251.39.206
// --- google.com ping statistics ---

//be carefull on exit code

// convert host address google.com -> X.X.X.X:XXXX
char	*host_convert(char *addr)
{
	struct addrinfo	hints, *res, *res0;
	
	int		error;
	char	*ip_v4_str = ip_v4_str = (char*)malloc(INET_ADDRSTRLEN);
	if (!ip_v4_str)
	{
		printf("Error: ip_v4_str malloc() failed\n");
		exit(0);
	}
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM; //TCP STREAM SOCKET

	error = getaddrinfo(addr, "http", &hints, &res0);
	if (error < 0)
	{
		printf("Error: getaddrinfo error\n");
		exit(0);
	}
	
	for (res = res0; res; res = res->ai_next)
	{
		void	*addr;

		if (res->ai_family == AF_INET)
		{
			struct sockaddr_in *ip_v4 = (struct sockaddr_in *)res->ai_addr;
			addr = &(ip_v4->sin_addr);
			inet_ntop(res->ai_family, addr, ip_v4_str, INET_ADDRSTRLEN);
			printf(" %s : %s\n", "IPv4", ip_v4_str);
		}
	}
	freeaddrinfo(res0);
	return ip_v4_str;
}

int	ft_ping(char *cmd)
{
	struct sockaddr_in	srcaddr, hostaddr;
	struct hostent		*hp;
	struct protoent		*proto;
	
	char	*hostname;
	char	*ip_str = host_convert(cmd);
	int		s;
	int		datalen;

	memset(&srcaddr, 0, sizeof(srcaddr));

	//int		inet = inet_pton(AF_INET, ip_str, &(servaddr.sin_addr));

	printf("ip_str -> %s\n", ip_str);
	bzero((char *)&hostaddr, sizeof(struct sockaddr_in *));
	srcaddr.sin_family = AF_INET;
	srcaddr.sin_addr.s_addr = inet_addr(ip_str);
	srcaddr.sin_port = htons(0);

	hp = gethostbyname(cmd);
	if (hp)
	{
		hostaddr.sin_family = hp->h_addrtype;
		bcopy(hp->h_addr, (caddr_t)&hostaddr.sin_addr, hp->h_length);
		hostname = hp->h_name;
	}
	else
	{
		printf("ping: cannot resolve %s: Unknown host", hp->h_name);
		exit(1);
	}

	if ((proto = getprotobyname("icmp")) == NULL)
	{
		fprintf(stderr, "icmp: unknown protocol\n");
		exit(10);
	}

	if ((s = socket(AF_INET, SOCK_RAW, proto->p_proto)) < 0)
	{
		perror("ft_ping: socket");
		exit(5);
	}

	datalen = 0;
	if (hostaddr.sin_family == AF_INET)
		printf("PING %s (%s): %d data bytes\n", hostname, inet_ntoa(hostaddr.sin_addr), datalen);
	else
		printf("PING %s: %d data bytes\n", hostname, datalen);
	setlinebuf(stdout);
	return 0;
}
