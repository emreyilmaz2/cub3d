/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:05:23 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/04 18:05:24 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	exit_func(char *err, t_cub3d *img)
{
	write(2, "Error\n", 6);
	write(2, err, ft_strlen2(err));
	free_all(img);
	exit(0);
}

void	exit_func3(t_cub3d *img)
{
	free_all(img);
	exit(0);
}

void	exit_func2(char *err)
{
	write(2, err, ft_strlen(err));
	exit(1);
}

void	exit_split_func(char **split, t_cub3d *img)
{
	int (i) = 0;
	write(2, split[1], ft_strlen(split[1]));
	free_all(img);
	while (split[i])
		free(split[i++]);
	free(split);
	exit(0);
}

void	exit_double_split_func(char **split, char **color, t_cub3d *img)
{
	int (i) = 0;
	write(2, split[1], ft_strlen(split[1]));
	free_all(img);
	while (split[i])
		free(split[i++]);
	free(split);
	i = 0;
	while (color[i])
		free(color[i++]);
	free(color);
	exit(0);
}
