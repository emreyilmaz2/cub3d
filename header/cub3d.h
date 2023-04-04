#ifndef CUB3D_H
# define CUB3D_H
#include "../mlx/mlx.h"
#include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/source/libft.h"

// black 000000
// cream FFFDD0
// dark cream fff39

# define KEY_ESC				53
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_W					13
# define KEY_LEFT				123
# define KEY_DOWN				125
# define KEY_RIGHT				124
# define KEY_UP					126
# define KEY_SHIFT				257
# define KEY_E					14
# define KEY_T					17

typedef struct s_game
{
	void	*mlx;
	void	*window;
	int		map_length;
	int		map_height;
	void	*wall;
	void	*character;
	void	*floor;
	void	*game_img;
	void	*map_img;
	void	*ray_img;
	int		*ray_addr;
	int		*character_addr;

	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		*game_addr;
	int		*map_addr;
	int		img_pixel;
	int		flag;
	int		character_x;
	int		character_y;

	double		map_player_x;
	double		map_player_y;
	double	angle;
	char	**directions;
	char	**floor_ceil;
	char	**map;
	bool	key_d;
	bool	key_a;
	bool	key_s;
	bool	key_w;
	bool	key_r;
	bool	key_l;
}	t_game;

char	*get_next_line(int fd);
char **mapcontrol(char *av, t_game *mlx);
int main(int ac, char **av);
void	start_game(char *str, t_game *mlx);
void	check_cub_file(t_game	*mlx);
int	ft_strcmp(const char *s1, const char *s2);
void	raycasting(double x, double y, t_game *game);

// keys action
void	keys_action_w(int x, int y, t_game *game);
void	keys_action_a(int x, int y, t_game *game);
void	keys_action_s(int x, int y, t_game *game);
void	keys_action_d(int x, int y, t_game *game);
void	keys_action(int x, int y, t_game *game);


// utils
int		two_dim_len(char **str);
void	two_dim_free(char **str);
int		find_height(int fd);
int		ft_max_x(char **map);
#endif
