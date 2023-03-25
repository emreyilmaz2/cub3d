#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif // !BUFFER_SIZE

char	*get_next_line(int fd);
size_t	ft_strlcpy_g(char *dest, const char *src, size_t size);
int		ft_strlen_g(const char *s);
char	*ft_strdup_g(const char *str);
char	*ft_strjoin_g(char *left_str, char *buff);
size_t	ft_strlcat_g(char *dst, const char *src, size_t dstsize);


#endif
