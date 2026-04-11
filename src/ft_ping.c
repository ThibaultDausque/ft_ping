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

// convert host address google.com -> X.X.X.X:XXXX
char	*host_convert(char *addr)
{
	struct addrinfo	hints, *res, *res0;
	
	int		error;
	char	*ip_v4_str = (char*)malloc(INET_ADDRSTRLEN * sizeof(char));

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
			inet_ntop(res->ai_family, addr, ip_v4_str, sizeof ip_v4_str);
			printf(" %s : %s\n", "IPv4", ip_v4_str);
		}
	}
	freeaddrinfo(res0);
	return ip_v4_str;
}

int	ft_ping(char *cmd)
{
	struct sockaddr_in	servaddr;

	int		sockfd = 0;
	char	*ip_str = host_convert(cmd);
	int		inet = inet_pton(AF_INET, ip_str, &(servaddr.sin_addr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(inet);

    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("Error: bind error\n");
        exit(1);
    }
    if (listen(sockfd, 10) != 0)
    {
		printf("Error: listen error\n");
		exit(1);
	}
	return 0;
}
