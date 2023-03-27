/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emreyilmaz <emreyilmaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:48:18 by emyilmaz          #+#    #+#             */
/*   Updated: 2022/04/07 06:30:55 by emreyilmaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	n_len;
	char	*hay;

	i = 0;
	hay = (char *)haystack;
	n_len = ft_strlen(needle);
	if (n_len == 0 || haystack == needle)
		return (hay);
	while (hay[i] != '\0' && i < len)
	{
		c = 0;
		while (hay[i + c] != '\0' && needle[c] != '\0'
			&& hay[i + c] == needle[c] && i + c < len)
				c++;
		if (c == n_len)
			return (hay + i);
		i++;
	}
	return (0);
}

int	ft_strstr(const char *s1, const char *s2)
{
    int i;
	printf("test\n\n\n\n\n\n");
    i = 0;
    if (!s1 || !s2)
        return (0);
	printf("bu butun string %s\nbu da aranan -> %s\n", s1, s2);
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
	printf("%c\n%c", s1[i], s2[i]);
    if (s1[i] == s2[i])
        return (1);
    return (0);
}

/*
int main()
{
    char x[] = "yalansa dogru de";
    char y[] = "do";
    printf("%s", ft_strnstr(x, y, 10));
}
*/
