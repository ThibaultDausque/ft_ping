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

// be carefull on exit code

// convert host address google.com -> X.X.X.X:XXXX

void	host_addr(char *hostname)
{
	//getaddrinfo(), returns a list of addr struct
	int						s, sfd;
	char					buf[BUF_SIZE];
	ssize_t					nread;
	socklen_t				peer_addrlen;
	struct addrinfo			hints;
	struct addrinfo			*result, *rp;
	struct sockaddr_storage	peer_addr;

	memset(&hints, 0, sizeof(hints));
	hints.ai_protocol = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
   	hints.ai_next = NULL;

	s = getaddrinfo(NULL, hostname, &hints, &result);
	if (s != 0)
	{
		perror("Error: getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	for (rp = result; rp != NULL; rp = rp->next)
	{
		char	host[1024], service[1024];
		peer_addrlen = sizeof(peer_addr);
		sfd = socket(rp-ai_family, rp->ai_socktype,
					rp->ai_protocol);
		if (sfd == -1)
			continue ;
		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
		{
			char	buf[1024];
			nread = recvfrom(sfd, buf, sizeof(buf), 0
						(struct sockaddr *)&peer_addr, &peer_addrlen);
			printf("Received %zd bytes from %s:%s\n",
				nread, host, service);	
			break ;
		}
		close(sfd)
	}


}

int	ft_ping(char *cmd)
{
	struct icmp			*icmp;
	struct sockaddr_in	ipv4_sock;

	void	*host_addr = host_convert(cmd);
	int		icmp_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	char	recv_buf[1024];

	if (icmp_sock < 0)
	{
		perror("Error: socket");
		exit(1);
	}

	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;

	ipv4_sock.sin_family = AF_INET;
	ipv4_sock.sin_addr.s_addr = htonl(htons(host_addr));

	if (sendto(icmp_sock, &icmp, sizeof(icmp), 0,
		(struct sockaddr *)&ipv4_sock, sizeof(ipv4_sock)))
	{
		perror("Error: send() failed\n");
		exit(1);
	}
	
	if (recvfrom(icmp_sock, &recv_buf, sizeof(recv_buf), 0,
		(struct sockaddr *)&ipv4_sock, sizeof(ipv4_sock)) <= 0)
	{
		perror("Error: recvfrom() failed\n");
		exit(1);
	}
	printf("data received from %s : %s\n", cmd, recv_buf);
	return 0;
}