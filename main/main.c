#include "../header/cub3d.h"

int	key_hook1(int keycode, t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_TAB && game->check_tab == 1)
	{
		game->key_tab = true;
		game->check_tab = 0;
	}
	else if (keycode == KEY_TAB && game->check_tab == 0)
	{
		game->key_tab = false;
		game->check_tab = 1;
	}
	if (keycode == KEY_D)
		game->key_d = true;
	if (keycode == KEY_A)
		game->key_a = true;
	if (keycode == KEY_S)
		game->key_s = true;
	if (keycode == KEY_W)
		game->key_w = true;
	if (keycode == KEY_LEFT)
		game->key_l = true;
	if (keycode == KEY_RIGHT)
		game->key_r = true;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_D)
		game->key_d = false;
	if (keycode == KEY_A)
		game->key_a = false;
	if (keycode == KEY_S)
		game->key_s = false;
	if (keycode == KEY_W)
		game->key_w = false;
	if (keycode == KEY_LEFT)
		game->key_l = false;
	if (keycode == KEY_RIGHT)
		game->key_r = false;
	return (0);
}

void	my_mlx_pixel_put(t_game *mlx, int y, int x, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < mlx->img_pixel)
	{
		i = 0;
		while (i < mlx->img_pixel)
		{
			mlx->map_addr[(mlx->img_pixel * y + i) * ft_max_x(mlx->map)
				* mlx->img_pixel + (mlx->img_pixel * x) + j] = color;
			i++;
		}
		j++;
	}
}

void	put_pixel(t_game *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (mlx->map[y])
	{
		x = 0;
		while (mlx->map[y][x])
		{
			if (mlx->map[y][x] == '1')
				my_mlx_pixel_put(mlx, y, x, 0x008080);
			else if (mlx->map[y][x] == '0')
				my_mlx_pixel_put(mlx, y, x, 0xFFFFFF);
			x++;
		}
		y++;
	}
	mlx->character = mlx_new_image(mlx, mlx->img_pixel / 2, mlx->img_pixel / 2);
	mlx->character_addr = (int *)mlx_get_data_addr
		(mlx->character, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	int (i) = 0;
	while (i < (mlx->img_pixel / 2) * (mlx->img_pixel / 2))
		mlx->character_addr[i++] = 0xff0000;
}

void	put_transparent(t_game *img)
{
	int (i) = -1;
	img->map_height = two_dim_len(img->map);
	img->map_length = ft_max_x(img->map);
	while (++i < img->map_length * img->img_pixel
		* img->map_height * img->img_pixel)
	{
		img->map_addr[i] = 0xFF000000;
	}
}

void	start_game(char *str, t_game *mlx)
{
	void	*img;
	int		*img_addr;
	char	**map;

	mlx->img_pixel = 17;
	int (i) = -1;
	mlx->map = mapcontrol(str, mlx);
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, 1366, 768, "cub3d");
	mlx->game_img = mlx_new_image(mlx, 1366, 768);
	mlx->map_img = mlx_new_image(mlx, ft_max_x(mlx->map)
			* mlx->img_pixel, two_dim_len(mlx->map) * mlx->img_pixel);
	mlx->ray_img = mlx_new_image(mlx, ft_max_x(mlx->map)
			* mlx->img_pixel, two_dim_len(mlx->map) * mlx->img_pixel);
	mlx->game_addr = (int *)mlx_get_data_addr(mlx->game_img,
			&mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	mlx->map_addr = (int *)mlx_get_data_addr(mlx->map_img,
			&mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	mlx->ray_addr = (int *)mlx_get_data_addr(mlx->ray_img,
			&mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	put_transparent(mlx);
	put_pixel(mlx);
	while (++i < 1366 * 384)
		mlx->game_addr[i] = 0x977141;
	while (++i < 1366 * 768)
		mlx->game_addr[i] = 0x808080;
	//mlx_put_image_to_window(mlx, mlx->window, mlx->game_img, 0, 0);
	//mlx_put_image_to_window(mlx, mlx->window, mlx->map_img, 0, 0);
}

void	cub3_inits(t_game *game)
{
	game->key_tab = false;
	game->key_a = false;
	game->key_s = false;
	game->key_d = false;
	game->key_w = false;
	game->key_r = false;
	game->key_l = false;
	game->check_tab = 1;
}

void	draw_3d(t_game *game, int ray_count, double distance)
{
	// printf("->>%f\n", distance);
	distance = distance * (double)game->img_pixel
		* ((double)768 / (double)1366);
	int (img_loc) = 1366 * (768 / 2) + 1366;
	img_loc -= ray_count;
	double line_len;
	if (distance != 0.0)
		line_len = (((double)768 / 2.0) / distance) * (double)game->img_pixel;
	else
		line_len = 768 * 5;
	// printf("->>%f\n", line_len);
	int (i) = 0;
	while (i < line_len/100000 && img_loc - (i * 1366) > 0 && img_loc + (i * 1366) < 1366 * 768)
	{
		if (img_loc - (i * 1366) > 0)
			game->game_addr[(int)img_loc - (i * 1366)] = 0x001111;
		if (img_loc + (i * 1366) < 1366 * 768)
			game->game_addr[(int)img_loc + (i * 1366)] = 0x00eeee;
		i++;
	}
}

void	ray_horizontal_while(t_game *game, bool *hit, double angle)
{
	while (game->character_x + game->hdx * game->dirx >= 0
		&& game->character_x + game->hdx * game->dirx <= (ft_max_x(game->map) - 1)
		&& game->character_y + game->hdy * game->diry - 0.0001 >= 0.0
		&& game->character_y + game->hdy * game->diry - 0.0001 <= two_dim_len(game->map))
	{
		game->hdy = game->hdy + 0.0001;
		if (game->map[(int)(game->character_y + game->hdy * game->diry)][(int)(game->character_x + game->hdx * game->dirx)] != '1')
		{
			*hit = true;
			game->newtwo_x = game->hdx * game->dirx;
			game->newtwo_y = game->hdy * game->diry;
			game->ray_x_h = game->character_x + game->newtwo_x;
			game->ray_y_h = game->character_y + game->newtwo_y;
			break ;
		}
		game->hdy = game->hdy + 1 - 0.0001;
		game->hdx = fabs(game->hdy / tan(angle * (M_PI / 180)));
	}
}

void	ray_vertical_while(t_game *game, bool *hit, double angle)
{
	while (game->character_x + game->vdx * game->dirx - 0.0001 >= 0.0
		&& game->character_x + game->vdx * game->dirx - 0.0001 <= (ft_max_x(game->map) - 1)
		&& game->character_y + game->vdy * game->diry >= 0.0
		&& game->character_y + game->vdy * game->diry <= two_dim_len(game->map))
	{
		game->vdx = game->vdx + 0.0001;
		if (game->map[(int)(game->character_y + game->vdy * game->diry)][(int)(game->character_x + game->vdx * game->dirx)] != '1')
		{
			*hit = true;
			game->new_x = game->vdx * game->dirx;
			game->new_y = game->vdy * game->diry;
			game->ray_x_v = game->character_x + game->new_x;
			game->ray_y_v = game->character_y + game->new_y;
			break ;
		}
		game->vdx = game->vdx + 1 - 0.0001;
		game->vdy = fabs(tan(angle * (M_PI / 180)) * game->vdx);
	}
}

double	horizontal(t_game *game, double angle, bool *hit)
{
	double	distance;
	if (game->diry == -1)
		game->hdy = game->character_y - floor(game->character_y);
	else
		game->hdy = ceil(game->character_y) - game->character_y;
	game->hdx = fabs(game->hdy / tan(angle * (M_PI / 180)));
	game->newtwo_x = game->hdx * game->dirx;
	game->newtwo_y = game->hdy * game->diry;
	ray_horizontal_while(game, hit, angle);
	if (*hit == true)
		distance = sqrt((game->newtwo_x * game->newtwo_x) \
			+ (game->newtwo_y * game->newtwo_y));
	else
		distance = 10000;
	return (distance);
}

double	vertical(t_game *game, double angle, bool *hit)
{
	double	distance;
	if (game->dirx == -1)
		game->vdx = game->character_x - floor(game->character_x);
	else
		game->vdx = ceil(game->character_x) - game->character_x;
	game->vdy = fabs(tan(angle * (M_PI / 180)) * game->vdx);
	game->new_x = game->vdx * game->diry;
	game->new_y = game->vdy * game->diry;
	ray_vertical_while(game, hit, angle);
	if (*hit == true)
		distance = sqrt((game->new_x * game->new_x) + (game->new_y * game->new_y));
	else
		distance = 10000;
	return (distance);
}

void	dda(t_game *game, int x, int y, int ray_c, double angle)
{
	double	distance;
	double	original_distance;

	game->dirx = ((cos(angle * (M_PI / 180)) > 0) * 2) - 1;
	game->diry = ((sin(angle * (M_PI / 180)) > 0) * -2) + 1;

	game->distance_v = vertical(game, angle, &game->hit_v);
	game->distance_h = horizontal(game, angle, &game->hit_h);
	if (game->distance_v < game->distance_h)
	{
		distance = game->distance_v;
		game->hit_v = true;
		game->hit_h = false;
	}
	else
	{
		distance = game->distance_h;
		game->hit_h = true;
		game->hit_v = false;
	}
	original_distance = distance;
	distance *= fabs(cos(((game->angle * (180.0 / M_PI)) - angle) * (M_PI / 180)));
	draw_3d(game, ray_c, distance);
}

void	raycasting(int x, int y, t_game *game)
{
	double (i) = -1;
	// int (yy) = (int)y * game->img_pixel * game->map_length;
	// int (xx) = (int)x / game->img_pixel;
	int	temp;
	game->map_height = two_dim_len(game->map);
	game->map_length = ft_max_x(game->map);
	while (++i < game->map_length * game->img_pixel
		* game->map_height * game->img_pixel)
	{
		game->ray_addr[(int)i] = 0xFF000000;
	}
	int len = game->map_length * game->img_pixel;
	int y2;
	int x2;
	int ray_count = 0;
	double angle = game->angle - (FOV / 2);
	i = -1;
	while (++i < 1366 * 384)
		game->game_addr[(int)i] = 0x977141;
	while (++i < 1366 * 768)
		game->game_addr[(int)i] = 0x808080;
	while (ray_count < 1366)
	{
		y2 = y;
		x2 = x;
		i = 0;
		while (1)//&& (y / game->img_pixel) - ((340 * i) / game->img_pixel) > 0 && game->map[(y * (game->map_length * game->img_pixel)) - (340 * i) / game->map_length / game->img_pixel][x / game->img_pixel])
		{
			y2 = ((y - (int)(sin(angle * (M_PI / 180)) * i)) / game->img_pixel);
			x2 = ((x + (int)(cos(angle * (M_PI / 180)) * i)) / game->img_pixel);
			if (game->map[y2][x2] != '1')
				game->ray_addr[
					(y - (int)(sin(angle * (M_PI / 180)) * i)) * len +
					(x + (int)(cos(angle * (M_PI / 180)) * i))] = 0x010000;
			else
			{
				// draw_3d(game, ray_count, i);
				break;
			}
			i += 0.5;
		}
		dda(game, x, y, ray_count, angle);
		angle += (double)FOV / (double)1366;
		ray_count++;
	}
}

int	game_loop(t_game *game)
{
	int (x) = game->map_player_x + (game->img_pixel / 4);
	int (y) = game->map_player_y + (game->img_pixel / 4);

	if (game->key_r)
		game->angle -= 5;
	if (game->key_l)
		game->angle += 5;

	while (game->angle < 0)
		game->angle += 360;
	while (game->angle >= 360)
		game->angle -= 360;
	keys_action(x, y, game);
	raycasting(x, y, game);

	mlx_put_image_to_window(game, game->window, game->game_img, 0, 0);
	if(game->key_tab)
	{
		mlx_put_image_to_window(game, game->window, game->map_img, 0, 0);
		mlx_put_image_to_window(game, game->window, game->character, game->map_player_x ,game->map_player_y);
		mlx_put_image_to_window(game, game->window, game->ray_img, 0, 0);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_game	game;
	if (ac == 2)
	{
		game.path = ft_strdup(av[1]);
		start_game(av[1], &game);
	}
	else
	{
		printf("yanlış argüman");
		exit(1);
	}
	cub3_inits(&game);
	mlx_hook(game.window, 17, (0L), key_hook1, &game);//close
	mlx_hook(game.window, 2, (1L), key_press, &game);
	mlx_hook(game.window, 3, (1L), key_release, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free(game.path);
	return 0;
}
