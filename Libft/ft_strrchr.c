/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturna <tturna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:54:46 by tturna            #+#    #+#             */
/*   Updated: 2022/02/18 15:22:16 by tturna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			ptr = (char *)(s + i);
		i++;
	}
	if (s[i] == (char)c)
		ptr = (char *)(s + i);
	return (ptr);
}

/*
#include <string.h>

int main () {
   int len;
   const char str[] = "tuna.test.42";
   const char ch = '.';
   char *ret;

   ret = ft_strrchr(str, ch);

   printf("|%c| > |%s|\n", ch, ret);

   return(0);
}
*/
