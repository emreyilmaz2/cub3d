/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:08:09 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/04 18:08:10 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_color(t_cub3d *img)
{
	int (i) = 0;
	img->ut_color = ft_split(img->split[1], ',');
	while (i < 3)
	{
		if (!img->ut_color[i] || !is_number(img->ut_color[i])
			|| ft_atoi(img->ut_color[i]) > 255 || ft_atoi(img->ut_color[i]) < 0)
			exit_double_split_func(img->split, img->ut_color, img);
		else if (strcmp(img->split[0], "F") == 0)
		{
			img->f_color[i] = ft_atoi(img->ut_color[i]);
			if (i == 2)
				img->f = 1;
		}
		else if (strcmp(img->split[0], "C") == 0)
		{
			img->c_color[i] = ft_atoi(img->ut_color[i]);
			if (i == 2)
				img->c = 1;
		}
		i++;
	}
}

int	isargtrue2(char *str)
{
	int	len;

	len = ft_strlen2(str);
	if (str[len - 1] != 'm'
		&& str[len - 2] != 'p'
		&& str[len - 3] != 'x'
		&& str[len - 4] != '.')
	{
		write(2, "\033[1;31mWrong XPM format!\n\033[0m", 30);
		exit(1);
	}
	return (0);
}

void	texture_check(t_cub3d *img)
{
	if (img->no == 1 && img->so == 1 && img->we == 1
		&& img->ea == 1 && img->f == 1 && img->c == 1)
		img->texture_bool = 1;
}
