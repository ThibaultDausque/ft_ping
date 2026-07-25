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

// ip header
typedef struct ip_t
{
	unsigned int	ip_v:4;
	unsigned int	ip_ihl:4;
	u_int8_t		tos;
	u_int8_t		ip_length;
	u_int16_t		ip_id;
	unsigned int	ip_flags:4;
	u_int16_t		ip_off;
	u_int8_t		ip_ttl;
	u_int8_t		ip_p;
	u_int16_t		ip_sum;
}	ip_s;

// ping.c
char*	parse_addr(char *addr);


#endif