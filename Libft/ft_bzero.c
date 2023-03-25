/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturna <tturna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:49:36 by tturna            #+#    #+#             */
/*   Updated: 2022/02/18 14:53:03 by tturna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*suc;

	i = 0;
	suc = (unsigned char *)s;
	while (i < n)
	{
		suc[i] = 0;
		i++;
	}
	s = suc;
}
/*

#include <stdio.h>

int main(void)
{
    char b[5] = "bzero";

    ft_bzero(b, 1);
	printf("%c", b[0]); // NULL (index 0)
	printf("%c", b[1]); // z (index 1)
    return (0);
}
*/

// void ile memory de işlem görür 
// size_ t değeri kadar fonksiyona zero atar
//her tanımlı elemana null değer yazdırır