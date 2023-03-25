/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturna <tturna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:56:03 by tturna            #+#    #+#             */
/*   Updated: 2022/02/18 15:38:40 by tturna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && (str1[i] || str2[i]))
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str2[i] > str1[i])
			return (-1);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int main( void )
{
    const char *cp1 = "Bilgisayar";
    const char *cp2 = "Bilgileri";
    int ret;

    ret = strncmp(cp1, cp2, 5);

    if(ret<0) printf("cp1 karakter dizisi 
	cp2 karakter dizisinden küçüktür!");
    else if(ret>0) printf("cp2 karakter 
	dizisi cp1 karakter dizisinden küçüktür!");
    else printf("cp1 karakter dizisi cp2 karakter dizisine eşittir!");

    return 0;
}
*/

//s1 stringi s2 stirnginden uzunsa 1 değilse -1 dondürür