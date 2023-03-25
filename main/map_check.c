#include "../header/cub3d.h"


char **mapcontrol(char *av, int i, int t, t_game *mlx)
{
	int		fd;
	char	*line;
	char	**map;

	int len = 0;
	int player_count = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		exit (0);
	map = malloc(sizeof(char *)  * 1024);
	line = get_next_line(fd);
	mlx->map_length = ft_strlen(line);
	while(line)
	{
		map[t] = line;
		line = get_next_line(fd);
		t++;
	}
	mlx->map_height = t;
	close(fd);
	return (map);
}
