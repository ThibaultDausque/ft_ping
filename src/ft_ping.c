#include <ft_ping.h>

// OUTPUT EXEMPLE
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

int	ft_ping(char **cmd)
{
	if (av[1] == -v && av[2] == "localhost")
	{

	}
}
