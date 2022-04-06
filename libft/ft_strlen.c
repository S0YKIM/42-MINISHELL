#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	size_t	length;

	if (!str)
		return (-1);
	length = 0;
	while (str[length])
		length++;
	return (length);
}
