/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturna <tturna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:30:40 by tturna            #+#    #+#             */
/*   Updated: 2022/02/18 15:36:30 by tturna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	char string[] = "Selam";
    char buffer[5];
    int r;

    r = ft_strlcpy(buffer, string, 6);

    printf("String '%s' Buffer '%s', Src Uzunluk %d\n",
            string,
            buffer,
            r
          );
}
*/

//hedefteki stringi kopyalayıp kayanağa yazdırır uzunluğunu verir