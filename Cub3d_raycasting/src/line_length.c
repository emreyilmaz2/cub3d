/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:05:49 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/04 18:05:50 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	line_length(t_cub3d *cub3dptr)
{
	int		fdmap;
	char	c;
	int		i;

	i = 0;
	fdmap = open(cub3dptr->map_input[1], O_RDONLY);
	while (read(fdmap, &c, 1) >= 1)
	{
		if (ft_strchr(&c, '\n'))
			i++;
	}
	close(fdmap);
	return (i);
}

int	column_length(t_cub3d *cub3dptr)
{
	int		fdmap;
	char	*line;
	int		i;

	fdmap = open(cub3dptr->map_input[1], O_RDONLY);
	line = get_next_line(fdmap);
	close(fdmap);
	i = ft_strlen2(line - 1);
	free(line);
	return (i);
}

/* map image address filling */
void	my_mlx_pixel_put(t_cub3d *img, int x, int y, int color)
{
	int (i) = 0;
	int (j) = 0;
	while (i < img->pixel)
	{
		j = 0;
		while (j < img->pixel)
		{
			img->addr_map[(img->pixel * y + i) * img->max_map_width
				* img->pixel + (img->pixel * x) + j] = color;
			j++;
		}
		i++;
	}
}

/* player to screen */
void	my_mlx_pixel_put2(t_cub3d *img)
{
	int (i) = -img->pixel / 4 + 1;
	int (j) = -img->pixel / 4 + 1;
	int (k) = -1;
	while (++k < img->max_map_width * img->pixel
		* img->max_map_height * img->pixel)
		img->addr_player[k] = 0xFF000000;
	while (++i < img->pixel / 4 - 2)
	{
		j = -img->pixel / 4 + 1;
		while (++j < img->pixel / 4 - 2)
			pixel_to_player_image_address(img, img->p_x * img->pixel
				+ j, img->p_y * img->pixel + i, RED);
	}
}

/* player pixel to map address and player image to window */
void	pixel_to_player_image_address(t_cub3d *img, int x, int y, int color)
{
	img->addr_player[(y * img->pixel * img->max_map_width) + x] = color;
}
