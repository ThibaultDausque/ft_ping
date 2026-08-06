#include "ft_ping.h"

char*	ft_substr(char *s, int start, int end)
{
	int		len = end - start;
	char*	result = (char*)malloc((len + 1) * sizeof(char));
	int		i = 0;

	if (!result)
		return NULL;

	while (start < end)
		result[i++] = s[start++];
	result[i] = '\0';
	return result;
}