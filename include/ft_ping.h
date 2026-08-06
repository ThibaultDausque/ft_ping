#ifndef FT_PING_H
# define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <unistd.h>

#define ICMP 1

#define TL 576
#define TTL 64
#define S_ADDR 2130706433
#define ICMP_ECHO 0
#define MAXPACKET 4096

// ip header
typedef struct ip_t
{
	unsigned int	ip_v:4;
	unsigned int	ip_ihl:4;
	u_int8_t		ip_tos;
	u_int8_t		ip_length;
	u_int16_t		ip_id;
	unsigned int	ip_flags:4;
	u_int16_t		ip_off;
	u_int8_t		ip_ttl;
	u_int8_t		ip_p;
	u_int16_t		ip_cksum;
	u_int32_t		ip_saddr;
	u_int32_t		ip_daddr;
}	ip_s;

typedef struct icmp_t
{
	u_int8_t	icmp_type;
	u_int8_t	icmp_code;
	u_int16_t	icmp_cksum;
	u_int32_t	icmp_ctt;
	u_int16_t	icmp_id;
	u_int16_t	icmp_sn;
}	icmp_s;

// ping.c
int	parse_addr(char *addr);

// utils.c
char*	ft_substr(char *s, int start, int end);

#endif