#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	size;
	char	*result;

	if (!str)
		return (NULL);
	size = ft_strlen(str) + 1;
	result = (char *)malloc(size * sizeof(char));
	if (result)
		ft_strlcpy(result, str, size);
	return (result);
}
