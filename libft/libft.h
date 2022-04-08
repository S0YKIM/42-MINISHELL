#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *str);
void	*ft_memset(void *b, int c, size_t len);
int		ft_isdigit(int c);

#endif
