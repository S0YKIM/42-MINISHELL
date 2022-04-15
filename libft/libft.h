#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(const char *str);
void		*ft_memset(void *b, int c, size_t len);
int			ft_isdigit(int c);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_isspace(int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
long long	ft_atol(const char *str);

#endif
