/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturna <tturna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:59:46 by tturna            #+#    #+#             */
/*   Updated: 2022/02/18 14:57:52 by tturna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dsize;

	dsize = 0;
	while (dest[dsize] != '\0' && dsize < size)
		dsize++;
	i = dsize;
	while (src[dsize - i] && dsize + 1 < size)
	{
		dest[dsize] = src[dsize - i];
		dsize++;
	}
	if (i < size)
		dest[dsize] = '\0';
	return (i + ft_strlen(src));
}

/*
#include <string.h>
#include <stdio.h>

int main()
{
	char first[] = "Tuna";
	char last[] = "ecole";
	int r;
	int size = 10;// tuna ecole 9 HARF FULL COPY 9
	char buffer[size]; // total olabilcek değer yer açtık. (buffer)

	strcpy(buffer,first);
	r = ft_strlcat(buffer,last,size); // FUNCTION

	puts(buffer);
	printf("Dönen değer: %d\n",r);
	if( r > size )
		puts("Yazı full kopyalanmadı");
	else
		puts("Yazı full kopyalandı");

	return(0);
}

*/