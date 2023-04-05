#include "../header/cub3d.h"

int	key_hook1(int keycode, t_game *game)
{
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
	else if(keycode == KEY_TAB && game->check_tab == 0)
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
	int i;
	int j;

	j = 0;
	while(j < mlx->img_pixel)
	{
		i = 0;
		while(i < mlx->img_pixel)
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
	int y;
	int x;

	y = 0;
	while(mlx->map[y])
	{
		x = 0;
		while(mlx->map[y][x])
		{
			if(mlx->map[y][x] == '1')
				my_mlx_pixel_put(mlx, y, x, 0x008080);
			else if(mlx->map[y][x] == '0')
				my_mlx_pixel_put(mlx, y, x, 0xFFFFFF);
			x++;
		}
		y++;
	}
	mlx->character = mlx_new_image(mlx, mlx->img_pixel/2, mlx->img_pixel/2);
	mlx->character_addr = (int *)mlx_get_data_addr(mlx->character, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	int i = 0;
	while (i < (mlx->img_pixel/2) * (mlx->img_pixel/2))
		mlx->character_addr[i++] = 0xff0000;
}

void	put_transparent(t_game *img)
{
	int (i) = -1;
	img->map_height = two_dim_len(img->map);
	img->map_length = ft_max_x(img->map);
	while (++i < img->map_length * img->img_pixel
		* img->map_height* img->img_pixel)
	{
		img->map_addr[i] = 0xFF000000;
	}
}


void	start_game(char *str, t_game *mlx)
{
	int (i) = -1;
	void *img;
	int *img_addr;
	char **map;
	mlx->img_pixel = 17;

	mlx->map = mapcontrol(str, mlx);
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, 1366, 768, "cub3d");
	mlx->game_img = mlx_new_image(mlx, 1366, 768);
	mlx->map_img = mlx_new_image(mlx, ft_max_x(mlx->map) * mlx->img_pixel, two_dim_len(mlx->map) * mlx->img_pixel); // 34*16 ve 14*16
	mlx->ray_img = mlx_new_image(mlx, ft_max_x(mlx->map) * mlx->img_pixel, two_dim_len(mlx->map) * mlx->img_pixel); // 34*16 ve 14*16
	mlx->game_addr = (int *)mlx_get_data_addr(mlx->game_img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	mlx->map_addr = (int *)mlx_get_data_addr(mlx->map_img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	mlx->ray_addr = (int *)mlx_get_data_addr(mlx->ray_img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	put_transparent(mlx);
	put_pixel(mlx);
	while (++i < 1366*384)
		mlx->game_addr[i] = 0x977141;
	while (++i < 1366*768)
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

void draw_3d(t_game *game, int ray_count, int distance)
{//1366 768
	int img_loc = 1366 * (768 / 2) + 1366;
	img_loc -= ray_count;
	int line_len = 768 / distance * 9;
	int i = 0;
	while (i < line_len)
	{
		if (img_loc - (i * 1366) > 0 && img_loc + (i * 1366) < 1366 * 768)
		{
			game->game_addr[img_loc - (i * 1366)] = 0x000001 * distance;
			game->game_addr[img_loc + (i * 1366)] = 0x000001 * distance;
		}
		i++;
	}
}

void	raycasting(int x, int y, t_game *game)
{
	int (i) = -1;
	// int (yy) = (int)y * game->img_pixel * game->map_length;
	// int (xx) = (int)x / game->img_pixel;
	int temp;
	game->map_height = two_dim_len(game->map);
	game->map_length = ft_max_x(game->map);
	while (++i < game->map_length * game->img_pixel
		* game->map_height * game->img_pixel)
	{
		game->ray_addr[i] = 0xFF000000;
	}

	int len = game->map_length * game->img_pixel;
	int y2;
	int x2;
	int ray_count = 0;
	double angle = game->angle - (FOV / 2);
	i = -1;
	while (++i < 1366*384)
		game->game_addr[i] = 0x977141;
	while (++i < 1366*768)
		game->game_addr[i] = 0x808080;
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
					(x + (int)(cos(angle * (M_PI / 180)) * i))] = 0x010000 * i;
			else
			{
				draw_3d(game, ray_count, i);
				break;
			}
			i++;
		}
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
	// mlx_clear_window(game->mlx, game->window);
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
	return 0;
}
