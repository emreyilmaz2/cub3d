/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_length2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:05:58 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/06 12:36:55 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

/* rays to screen x 1200 */
/* fill addr -> paint for ceil and floor */
void	my_mlx_pixe_put_angle(t_cub3d *img)
{
	double (i) = 0;
	double (j) = -(double)ANGLE_CAMERA / 2.0;
	int (ray_counter) = 0;
	fill_addr(img);
	while (j <= (ANGLE_CAMERA / 2.0))
	{
		i = 0;
		while (1)
		{
			img->new_angle = img->angle - (j * DR);
			img->newp_x = (img->p_x * img->pixel) + (cos(img->new_angle) * i);
			img->newp_y = (img->p_y * img->pixel) - (sin(img->new_angle) * i);
			if (img->map[(int)(img->newp_y / img->pixel)]
				[(int)(img->newp_x / img->pixel)] == '0')
				pixel_to_ray_image_address(img, img->newp_x,
					img->newp_y, GREEN);
			else
				break ;
			i++;
		}
		raycasting(img, (img->angle * (180.0 / PI))
			+ j, ray_counter);
		j += (ANGLE_CAMERA / 2.0) / (WINDOW_WIDTH / 2.0);
		ray_counter++;
	}
}

void	fill_addr(t_cub3d *img)
{
	int (k) = -1;
	int (l) = 0;
	while (l < WINDOW_HEIGHT * WINDOW_WIDTH / 2.0)
			img->addr_game[l++] = img->c_final;
	while (l < WINDOW_HEIGHT * WINDOW_WIDTH)
			img->addr_game[l++] = img->f_final;
	while (++k < img->max_map_width * img->pixel
		* img->max_map_height * img->pixel)
		img->addr_ray[k] = 0xFF000000;
}

/* ray pixel to map address and player image to window */
void	pixel_to_ray_image_address(t_cub3d *img, int x, int y, int color)
{
	img->addr_ray[(y * img->pixel * img->max_map_width) + x] = color;
}

/* 0 north, 1 south, 2 east, 3 west */
void	add_xpm(t_cub3d *img)
{
	int (i) = -1;
	img->xpm[0].img.ptr = mlx_xpm_file_to_image(img->mlx,
			img->no_path, &img->xpm[0].height, &img->xpm[0].width);
	img->xpm[1].img.ptr = mlx_xpm_file_to_image(img->mlx,
			img->so_path, &img->xpm[1].height, &img->xpm[1].width);
	img->xpm[2].img.ptr = mlx_xpm_file_to_image(img->mlx,
			img->ea_path, &img->xpm[2].height, &img->xpm[2].width);
	img->xpm[3].img.ptr = mlx_xpm_file_to_image(img->mlx,
			img->we_path, &img->xpm[3].height, &img->xpm[3].width);
	while (++i < 4)
	{
		img->xpm[i].img.addr = (int *)mlx_get_data_addr(img->xpm[i].img.ptr,
				&img->xpm[i].img.bpp, &img->xpm[i].img.line_size,
				&img->xpm[i].img.endian);
	}
}

/* map image for each 1 and 0 char */
void	putpixel(t_cub3d *cub3dptr)
{
	int	x;
	int	y;

	add_xpm(cub3dptr);
	y = 0;
	while (cub3dptr->map[y])
	{
		x = 0;
		while (cub3dptr->map[y][x])
		{
			if (cub3dptr->map[y][x] == '1')
				my_mlx_pixel_put(cub3dptr, x, y, 0x008080);
			else if (cub3dptr->map[y][x] == '0')
				my_mlx_pixel_put(cub3dptr, x, y, WHITE);
			x++;
		}
		y++;
	}
}
