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
	mlx->window = mlx_new_window(mlx->mlx, MAP_WIDTH, MAP_HEIGHT, "cub3d");
	mlx->game_img = mlx_new_image(mlx, MAP_WIDTH, MAP_HEIGHT);
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
	while (++i < MAP_WIDTH * (MAP_HEIGHT / 2))
		mlx->game_addr[i] = 0x977141;
	while (++i < MAP_WIDTH * MAP_HEIGHT)
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
	game->hit_h = false;
	game->hit_v = false;
	game->check_tab = 1;
}

void	draw_3d(t_game *game, int ray_count, double distance)
{
	int (i) = 0;
	distance = distance * (double)game->img_pixel
		* ((double)MAP_HEIGHT / (double)MAP_WIDTH);
	double rate = (((double)MAP_WIDTH / 2.0) / distance) * (double)game->img_pixel;
	if(rate >= 4000)
		rate = 4000;
	while (i <= rate && i <= (MAP_HEIGHT / 2.0))
	{
		game->game_addr[((MAP_HEIGHT / 2) * MAP_WIDTH - ray_count) + (MAP_WIDTH * i)] = 0x003600;
		game->game_addr[((MAP_HEIGHT / 2) * MAP_WIDTH - ray_count) - (MAP_WIDTH * i)] = 0x5c3021;
		i++;
	}
}

int	is_wall_v2(double x, double y, t_game *img)
{
	int	tempx;
	int	tempy;

	tempx = (int)floor(x);
	tempy = (int)floor(y);
	return (ft_strchr("0NSEW", img->map[tempy][tempx]) == NULL);
}

void	ray_horizontal_while(t_game *game, bool *hit, double angle)
{
	while (game->character_x + game->hdx * game->dirx >= 0
		&& game->character_x + game->hdx * game->dirx <= 50
		&& game->character_y + game->hdy * game->diry - 0.0001 >= 0.0
		&& game->character_y + game->hdy * game->diry - 0.0001 <= 14)
	{
		game->hdy = game->hdy + 0.0001;
		if (is_wall_v2(game->character_x + game->hdx * game->dirx, game->character_y + game->hdy * game->diry, game))
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
		if (is_wall_v2(game->character_x + game->vdx * game->dirx, game->character_y + game->vdy * game->diry, game))
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

void draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);

    while (x1 != x2 || y1 != y2)
    {
        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }

        mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
    }
}

void	dda(t_game *game, int x, int y, int ray_c, double angle)
{
	double	distance;
	double	original_distance;
	int x2, y2;

	//printf("DOGRU MU2 %f\n",game->angle); -> derece olarak
	//printf("%f\n",angle);
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
	x2 = game->character_x + distance * cos(angle * M_PI / 180);
	y2 = game->character_y + distance * sin(angle * M_PI / 180);
	original_distance = distance;
	distance *= fabs(cos(((game->angle) - angle) * (M_PI / 180)));
	draw_line(game->mlx, game->window, game->character_x, game->character_y, x2, y2, 0xFF0000);
	draw_3d(game, ray_c, distance);
}

void	raycasting(int x, int y, t_game *game)
{
	double (i) = -1;
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
	while (++i < MAP_WIDTH * (MAP_HEIGHT / 2))
		game->game_addr[(int)i] = 0x977141;
	while (++i < MAP_WIDTH * MAP_HEIGHT)
		game->game_addr[(int)i] = 0x808080;
	while (ray_count < MAP_WIDTH)
	{
		y2 = y;
		x2 = x;
		i = 0;
		while (1)//&& (y / game->img_pixel) - ((340 * i) / game->img_pixel) > 0 && game->map[(y * (game->map_length * game->img_pixel)) - (340 * i) / game->map_length / game->img_pixel][x / game->img_pixel])
		{
			//game->new_angle = game->angle - ()
			y2 = ((y - (int)(sin(angle * (M_PI / 180)) * i)) / game->img_pixel);
			x2 = ((x + (int)(cos(angle * (M_PI / 180)) * i)) / game->img_pixel);
			if (game->map[y2][x2] == '0')
				game->ray_addr[
					(y - (int)(sin(angle * (M_PI / 180)) * i)) * len +
					(x + (int)(cos(angle * (M_PI / 180)) * i))] = 0x010000 * i;
			else
				break;
			i++;
		}
		dda(game, x, y, ray_count, angle);
		angle += (double)FOV / (double)MAP_WIDTH;
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
		exit(printf("wrong arg count"));
	cub3_inits(&game);
	mlx_hook(game.window, 17, (0L), key_hook1, &game);//close
	mlx_hook(game.window, 2, (1L), key_press, &game);
	mlx_hook(game.window, 3, (1L), key_release, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free(game.path);
	return 0;
}
