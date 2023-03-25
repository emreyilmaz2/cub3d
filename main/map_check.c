#include "../header/cub3d.h"
#include "string.h"

int	find_height(int fd)
{
	int	len = 0;
	char *line;
	line = get_next_line(fd);
	while(line)
	{
		len++;
		line = get_next_line(fd);
	}
	return(len);
}

int	one_finder(char *first_line)
{
	int	len;

    len = -1;
	while(first_line[++len])
	{
        if(first_line[len] != '1' && first_line[len] != ' ' &&
            first_line[len] != 'N' && first_line[len] != 'W' &&
            first_line[len] != 'S' && first_line[len] != 'E' && first_line[len] != '\0')
        {
			return(0);
		}
	}
	return(1);
}

int is_empty(char *line)
{
	int	len;

	len = -1;
	while(line[++len])
	{
		if(line[len] > 32)
			return(0);
	}
	return(1);
}

char	**mapcontrol(char *av, t_game *mlx)
{
    int (fd);
    char (*line) = NULL;
    char (**map);
    int (cnt) = -1;
    int (res) = -1;
    int (gs) = -1;
    int (fc) = -1;

	int temp;
    fd = open(av, O_RDONLY);
    if (fd < 0)
        exit(0);
    mlx->map_height = find_height(fd);
    close(fd);
    fd = open(av, O_RDONLY);
    if (fd < 0)
        exit(0);
    mlx->directions = malloc(sizeof(char *) * 4);
    mlx->floor_ceil = malloc(sizeof(char *) * 2);
    while (++cnt < mlx->map_height)
	{
		line = get_next_line(fd);
		printf("geldim %d ve kontrol edicegim line %s\n", cnt, line);
		if(is_empty(line));
		else if(!ft_strcmp(line, "NO") || !ft_strcmp(line, "SO") || !ft_strcmp(line, "WE") || !ft_strcmp(line, "EA"))
			mlx->directions[++res] = strdup(line);
		else if((line[0] == 'F' && line[1] == ' ') || (line[0] == 'C' && line[1] == ' '))
			mlx->floor_ceil[++fc] = strdup(line);
		else if((temp = one_finder(line)) == 1)
			mlx->map[++gs] = strdup(line);
        else
        {

            printf("check map !  -> %d\n", temp);
            exit(0);
        }
    }
    close(fd);
    // check_directions(map);
    return (map);
}
