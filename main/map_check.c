#include "../header/cub3d.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

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
	off_t new_pos = lseek(fd, 0, SEEK_SET);
	return(len);
}

int	one_finder(char *first_line)
{
	int	len;

    len = -1;
	while(first_line[++len])
	{
        if(first_line[len] != '1' && first_line[len] != ' ' && first_line[len] != '0' &&
            first_line[len] != 'N' && first_line[len] != 'W' && first_line[len] != '\n' &&
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

void	ft_check_directions(char **directions)
{
	int (benten) = -1;
	int fd;
	char **null;
	char *bi;
	while(directions[++benten])
	{
		null = ft_split(directions[benten], ' ');
		if(!(ft_strstr(null[0], "NO") || ft_strstr(null[0], "SO") || ft_strstr(null[0], "WE") || ft_strstr(null[0], "EA")))
			exit(printf("direction name wrong!\n"));
		else if(null[2])
			exit(printf("direction line long"));
		bi = ft_strtrim(null[1], "\n");
		fd = open(bi, O_RDONLY);
		if(fd == -1)
			exit(printf("xpm file does not exist!\n"));
		free(bi);
		// two_dim_free(null);
	}
}

void	is_all_numeric(char **ptr) //200 100 0
{
	int (i) = 0;
	int (j) = 0;
	while(ptr[i])
	{
		printf("dnemee\n");
		j = 0;
		while(ptr[i][j])
		{
			printf("%c\n", ptr[i][j]);
			if(!ft_isdigit(ptr[i][j]))
				exit(printf("hexa color codes contains letter or something\n"));
			j++;
		}
		i++;
	}
}

void	ft_check_colors(char **color) // burda free yapmamiz gerek
{
	int (i) = 0;
	char ***null;
	null[0] = ft_split(color[0], ' ');
	null[1] = ft_split(null[0][1], ',');
	null[2] = ft_split(color[1], ' ');
	null[3] = ft_split(null[2][1], ',');
	printf("%c\n", null[2][0][0]);
	if(!((null[0][0][0] == 'F' && !null[0][0][1]) && (null[2][0][0] == 'C' && !null[2][0][1])))
		exit(printf("check hexa codes\n"));
	is_all_numeric(null[1]);
	is_all_numeric(null[3]);
}

void	ft_check_borders(char **map)
{

}

void	check_cub_file(t_game	*mlx)
{
	ft_check_directions(mlx->directions); //  yönler ve yanlarindakı dosyalarin açılabilirlik kontrolü
	ft_check_colors(mlx->floor_ceil); // renk kodları 0 ile 255 arasında mı kontol et
	ft_check_borders(mlx->map); // sınırlarda açıklık var mı kontrol
}

char	**mapcontrol(char *av, t_game *mlx)
{
	int roro[5] = {-1, -1, -1, -1, -1};
	char *line;
    char (**map);
    roro[0] = open(av, O_RDONLY);
    if (roro[0] < 0)
        exit(0);
    mlx->map_height = find_height(roro[0]);
    mlx->directions = malloc(sizeof(char *) * 4);
    mlx->floor_ceil = malloc(sizeof(char *) * 2);
    mlx->map = malloc(sizeof(char *) * 1024);
    while (++roro[1] < mlx->map_height)
	{
		line = get_next_line(roro[0]);
		if(is_empty(line));
		else if(!ft_strcmp(line, "NO") || !ft_strcmp(line, "SO") || !ft_strcmp(line, "WE") || !ft_strcmp(line, "EA"))
			mlx->directions[++roro[2]] = strdup(line);
		else if((line[0] == 'F' && line[1] == ' ') || (line[0] == 'C' && line[1] == ' '))
			mlx->floor_ceil[++roro[4]] = strdup(line);
		else if(one_finder(line))
			mlx->map[++roro[3]] = strdup(line);
        else
            exit(printf("check map !\n"));
    }
	mlx->directions[++roro[2]] = NULL;
	check_cub_file(mlx);
    close(roro[0]);
    return (map);
}
