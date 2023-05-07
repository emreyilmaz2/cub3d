/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:07:34 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/04 18:07:35 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	is_wall(double x, double y, t_cub3d *img)
{
	int	tempx;
	int	tempy;

	if (x < 0 || x > img->max_x || y < 0 || y > img->max_y)
		return (1);
	tempx = floor(x);
	tempy = floor(y);
	if (img->map[tempy][tempx] != '1')
		return (0);
	return (1);
}

int	is_wall_v2(double x, double y, t_cub3d *img)
{
	int	tempx;
	int	tempy;

	tempx = (int)floor(x);
	tempy = (int)floor(y);
	return (ft_strchr("0NSEW", img->map[tempy][tempx]) == NULL);
}

void	ray_vertical_while(t_cub3d *img, bool *hit, double angle)
{
	while (img->p_x + img->vdx * img->dirx - 0.0001 >= 0
		&& img->p_x + img->vdx * img->dirx - 0.0001 <= (img->max_map_width - 1)
		&& img->p_y + img->vdy * img->diry >= 0
		&& img->p_y + img->vdy * img->diry <= img->max_map_height)
	{
		img->vdx = img->vdx + 0.0001;
		if (is_wall_v2(img->p_x + img->vdx
				* img->dirx, img->p_y + img->vdy * img->diry, img))
		{
			*hit = true;
			img->tmp_x = img->vdx * img->dirx;
			img->tmp_y = img->vdy * img->diry;
			img->ray_x_v = img->p_x + img->tmp_x;
			img->ray_y_v = img->p_y + img->tmp_y;
			break ;
		}
		img->vdx = img->vdx + 1 - 0.0001;
		img->vdy = fabs(tan(angle * (PI / 180)) * img->vdx);
	}
}

void	ray_horizontal_while(t_cub3d *img, bool *hit, double angle)
{
	while (img->p_x + img->hdx * img->dirx >= 0 && img->p_x + img->hdx
		* img->dirx <= (img->max_map_width - 1)
		&& img->p_y + img->hdy * img->diry - 0.0001 >= 0
		&& img->p_y + img->hdy * img->diry - 0.0001 <= img->max_map_height)
	{
		img->hdy = img->hdy + 0.0001;
		if (is_wall_v2(img->p_x + img->hdx * img->dirx,
				img->p_y + img->hdy * img->diry, img))
		{
			*hit = true;
			img->tmptwo_x = img->hdx * img->dirx;
			img->tmptwo_y = img->hdy * img->diry;
			img->ray_x_h = img->p_x + img->tmptwo_x;
			img->ray_y_h = img->p_y + img->tmptwo_y;
			break ;
		}
		img->hdy = img->hdy + 1 - 0.0001;
		img->hdx = fabs(img->hdy / tan(angle * (PI / 180)));
	}
}

void	my3d_wall_control(t_cub3d *img, t_xpm xpm)
{
	if (img->_hith == true)
		img->find_pixel = (img->ray_x - floor(img->ray_x)) * xpm.width;
	else if (img->_hitv == true)
		img->find_pixel = (img->ray_y - floor(img->ray_y))
			* img->xpm[img->xpm_number].width;
}
