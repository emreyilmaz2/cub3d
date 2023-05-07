/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:06:12 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/05 14:35:17 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	check_all(t_cub3d *img)
{
	img->no = 0;
	img->so = 0;
	img->we = 0;
	img->ea = 0;
	isargtrue(img);
	mapcheck(img);
	if (!img->texture_bool || !img->map_bool)
		exit_func("\033[1;31mMap or texture error\033[0m", img);
	player(img);
	img->f_final = (img->f_color[0] << 16)
		+ (img->f_color[1] << 8) + (img->f_color[2]);
	img->c_final = (img->c_color[0] << 16)
		+ (img->c_color[1] << 8) + (img->c_color[2]);
}

void	free_all(t_cub3d *img)
{
	free(img->map);
	free(img);
}

void	initializer(t_cub3d *img)
{
	img->check->w_check = false;
	img->check->a_check = false;
	img->check->s_check = false;
	img->check->d_check = false;
	img->check->l_check = false;
	img->check->r_check = false;
	img->check->tab_check = true;
	img->n_timer = 0;
	img->s_timer = 0;
	img->e_timer = 0;
	img->w_timer = 0;
	img->f = 0;
	img->c = 0;
	img->texture_bool = 0;
	img->map_bool = 0;
	img->speed_pixel = 1;
	img->pixel = 16;
	img->max_map_width = 0;
	img->max_map_height = 0;
	img->angle = 0;
	img->speed = (double)img->speed_pixel / (double)img->pixel;
}

void	map_addr(t_cub3d *img)
{
	int (map) = 0;
	int (player) = 0;
	int (ray) = 0;
	int (game) = 0;
	img->img_game = mlx_new_image(img->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->img_map = mlx_new_image(img->mlx, img->max_map_width
			* img->pixel, img->max_map_height * img->pixel);
	img->img_player = mlx_new_image(img->mlx, img->max_map_width
			* img->pixel, img->max_map_height * img->pixel);
	img->img_ray = mlx_new_image(img->mlx, img->max_map_width
			* img->pixel, img->max_map_height * img->pixel);
	img->addr_game = (int *)mlx_get_data_addr(img->img_game,
			&game, &game, &game);
	img->addr_map = (int *)mlx_get_data_addr(img->img_map,
			&map, &map, &map);
	img->addr_player = (int *)mlx_get_data_addr(img->img_player,
			&player, &player, &player);
	img->addr_ray = (int *)mlx_get_data_addr(img->img_ray,
			&ray, &ray, &ray);
	put_transparent(img);
	putpixel(img);
}

int	main(int argc, char **argv)
{
	t_cub3d	*img;

	if (argc != 2)
		return (printf("\033[1;31mBad argument!\n\033[0m"));
	img = (t_cub3d *)malloc(sizeof(t_cub3d));
	img->check = (t_check *)malloc(sizeof(t_check));
	img->map_input = argv;
	initializer(img);
	check_all(img);
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	map_addr(img);
	mlx_hook(img->mlx_win, 2, 1L, key_press, &img->mlx);
	mlx_hook(img->mlx_win, 17, (0L), pushbutton, img);
	mlx_hook(img->mlx_win, 3, 1L << 1, key_release, &img->mlx);
	mlx_loop_hook(img->mlx, putimage, img);
	mlx_loop(img->mlx);
}
