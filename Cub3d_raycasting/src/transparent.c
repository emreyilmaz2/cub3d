/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:07:46 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/04 18:07:47 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	put_transparent(t_cub3d *img)
{
	int (i) = -1;
	while (++i < img->max_map_width * img->pixel
		* img->max_map_height * img->pixel)
	{
		img->addr_map[i] = 0xFF000000;
		img->addr_player[i] = 0xFF000000;
		img->addr_ray[i] = 0xFF000000;
	}
}
