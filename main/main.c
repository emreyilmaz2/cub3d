#include "../header/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	key_hook(int keycode, t_game *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->window, game->window);
		exit(0);
	}
	return (0);
}


void	start_game(char *str, t_game *mlx)
{
	void *img;
	int *img_addr;
	char **map;
	int i;

	i = 0;
	mlx->map = mapcontrol(str, -1, 0, mlx);
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, 800, 800, "cub3d");
	mlx->game_img = mlx_new_image(mlx, 800, 800);
	mlx->map_img = mlx_new_image(mlx, 9 * BOX_SIZE, 7 * BOX_SIZE);

	mlx->game_addr = (int *)mlx_get_data_addr(mlx->game_img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	mlx->map_addr = (int *)mlx_get_data_addr(mlx->map_img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);

	i = -1;
	int k = -1;

	while (k < 270 * 210)
		mlx->map_addr[++k] = 0x008000;
	while (++i < 800*400)
		mlx->game_addr[i] = 0x007fff;
	while (++i < 800*800)
		mlx->game_addr[i] = 0x808080;
	mlx_put_image_to_window(mlx, mlx->window, mlx->game_img, 0, 0);
	mlx_put_image_to_window(mlx, mlx->window, mlx->map_img, 0, 0);

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

	mlx_key_hook(game.window, key_hook, &game);

	mlx_loop(game.mlx);
	return 0;
}
