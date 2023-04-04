#include "../header/cub3d.h"

void	keys_action_w(int x, int y, t_game *game)
{
	if (game->map[(int)((y - sin(game->angle * (M_PI / 180))) / (double)game->img_pixel)][(int)(x / (double)game->img_pixel)] != '1')
		game->map_player_y -= sin(game->angle * (M_PI / 180));
	if (game->map[(int)(y / (double)game->img_pixel)][(int)((x + cos(game->angle * (M_PI / 180))) / (double)game->img_pixel)] != '1')
		game->map_player_x += cos(game->angle * (M_PI / 180));
}

void	keys_action_a(int x, int y, t_game *game)
{
	if (game->map[(int)((y - cos(game->angle * (M_PI / 180))) / (double)game->img_pixel)][(int)(x / (double)game->img_pixel)] != '1')
		game->map_player_y -= cos(game->angle * (M_PI / 180));
	if (game->map[(int)(y / (double)game->img_pixel)][(int)((x - sin(game->angle * (M_PI / 180))) / (double)game->img_pixel)] != '1')
		game->map_player_x-= sin(game->angle * (M_PI / 180));
}

void	keys_action_s(int x, int y, t_game *game)
{
	if (game->map[(int)((y + sin(game->angle * (M_PI / 180))) / (double)game->img_pixel)][(int)(x / (double)game->img_pixel)] != '1')
		game->map_player_y += sin(game->angle * (M_PI / 180));
	if (game->map[(int)(y / (double)game->img_pixel)][(int)((x - cos(game->angle * (M_PI / 180))) / (double)game->img_pixel)] != '1')
		game->map_player_x -= cos(game->angle * (M_PI / 180));
}

void	keys_action_d(int x, int y, t_game *game)
{
	if (game->map[(int)((y + cos(game->angle * (M_PI / 180))) / (double)game->img_pixel)][(int)(x / (double)game->img_pixel)] != '1')
		game->map_player_y += cos(game->angle * (M_PI / 180));
	if (game->map[(int)(y / (double)game->img_pixel)][(int)((x + sin(game->angle * (M_PI / 180))) / (double)game->img_pixel)] != '1')
		game->map_player_x += sin(game->angle * (M_PI / 180));
}

void	keys_action(int x, int y, t_game *game)
{
	if (game->key_w)
		keys_action_w(x, y, game);
	if (game->key_a)
		keys_action_a(x, y, game);
	if (game->key_s)
		keys_action_s(x, y, game);
	if (game->key_d)
		keys_action_d(x, y, game);
}