/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:08:03 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/04 18:08:04 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

char	*clear_endstr(char *str)
{
	int		i;
	char	*newstr;

	i = 0;
	while (str[i])
	{
		if (str[i] <= 32)
		{
			str[i] = 0;
			newstr = ft_strdup(str);
			free(str);
			return (newstr);
		}
		i++;
	}
	return (str);
}

int	is_number(char *str)
{
	int (i) = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] > '9' && str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}
