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

#define  BOX_SIZE 30

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

	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		*game_addr;
	int		*map_addr;
	int		flag;

	char	**directions;
	char	**floor_ceil;
	char	**map;
}	t_game;

char	*get_next_line(int fd);
char **mapcontrol(char *av, t_game *mlx);
int main(int ac, char **av);
void	start_game(char *str, t_game *mlx);
void	check_cub_file(t_game	*mlx);
int	ft_strcmp(const char *s1, const char *s2);
void	two_dim_free(char **str);

#endif
