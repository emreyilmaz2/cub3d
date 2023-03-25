#include "get_next_line.h"

size_t	ft_strlcpy_g(char *dest, const char *src, size_t size)
{
	size_t	srcsize;
	size_t	i;

	i = 0;
	srcsize = ft_strlen_g(src);
	if (!dest || !src)
		return (0);
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (srcsize);
}

size_t	ft_strlcat_g(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = ft_strlen_g(dst);
	slen = ft_strlen_g(src);
	if (dstsize <= dlen)
		return (dstsize + slen);
	i = 0;
	while (src[i] != '\0' && dlen < dstsize - 1)
	{
		dst[dlen] = src[i];
		dlen++;
		i++;
	}
	dst[dlen] = '\0';
	return (ft_strlen_g(dst) + ft_strlen_g(&src[i]));
}

int	ft_strlen_g(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_g(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen_g(left_str) + \
		ft_strlen_g(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen_g(left_str) + ft_strlen_g(buff)] = '\0';
	free(left_str);
	return (str);
}

char	*ft_strdup_g(const char *s1)
{
	char	*s2;
	size_t	i;

	i = ft_strlen_g(s1);
	s2 = (char *)malloc(sizeof(char) * (i + 1));
	if (!s2)
		return (0);
	ft_strlcpy_g(s2, (char *)s1, i + 1);
	return (s2);
}
