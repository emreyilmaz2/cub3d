#include "../header/cub3d.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

int	find_height(char *path)
{
	int (fd);
	int	(len) = 0;
	char (*line);
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	while(line)
	{
		len++;
		line = get_next_line(fd);
	}
	close(fd);
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
			return(0);
	}
	return(1);
}

int	ft_max_y(char *path)
{
	char (*str);
	int (y) = 0;
	int	fd;
	int	flag = 0;
	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	while(str)
	{
		if(one_finder(str))
		{
			printf("%s", str);
			flag = 1;
		}
		if(flag)
			y++;
		free(str);
		str = get_next_line(fd);
	}
	printf("y->>> %d\n", y);
	return(y);
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

void	is_all_numeric(char **ptr)
{
	int (i) = 0;
	int (j) = 0;
	while(ptr[i])
	{
		j = 0;
		while(ptr[i][j])
		{
			if(!ft_isdigit(ptr[i][j]) && ptr[i][j] != '\n')
				exit(printf("hexa color codes contains letter or something\n"));
			j++;
		}
		if(ft_atoi(ptr[i]) < 0 || ft_atoi(ptr[i]) > 255)
				exit(printf("255 i gectin gardas\n"));
		i++;
	}
}

void	ft_check_colors(char **color) // burda free yapmamiz gerek
{
	int (i) = 0;
	int (j) = 0;
	char ***ptr;
	ptr[0] = ft_split(color[0], ' ');
	ptr[1] = ft_split(ptr[0][1], ',');
	ptr[2] = ft_split(color[1], ' ');
	ptr[3] = ft_split(ptr[2][1], ',');
	if(!((ptr[0][0][0] == 'F' && !ptr[0][0][1]) && (ptr[2][0][0] == 'C' && !ptr[2][0][1])))
		exit(printf("check hexa codes\n"));
	if((two_dim_len(ptr[1]) > 3) || (two_dim_len(ptr[3]) > 3))
		exit(printf("more than requested hexa codes\n"));

	is_all_numeric(ptr[1]);
	is_all_numeric(ptr[3]);
}

void	ft_check_maps2(char **map)
{
	printf("fuck\n");
	int i = 0;
	int j = 0;
	int last_j = 0;
	while(map[j])
	{
		i = 0;
		while(map[j][i])
		{
			if (map[j][i] == '0')
			{
				last_j = j;
				while(map[j][i] && map[j][i] == '0')
					j--;
				if (map[j][i] == '\0' || map[j][i] == '\n' || map[j][i] == ' ')
					exit (printf("error haritas --%d--%d--%c--\n", j,i,map[j][i]));
				j = last_j;
				while(map[j][i] && map[j][i] == '0')
					j++;
				if (map[j][i] == '\0' || map[j][i] == '\n' || map[j][i] == ' ')
					exit (printf("error haritasa %c\n", map[j][i]));
				j = last_j;
			}
			i++;
		}
		j++;
	}
}

void	ft_check_maps(char	**map, int max_x)
{
	int i = 0,j = 0,size = 0;
	while(map[size])
		size++;
	size--;
	while(map[j])
	{
		while(map[j][i])
		{
			if((j == 0 || j == size) && (map[j][i] != '1' && map[j][i] != ' ' && map[j][i] != '\n'))
				exit(printf("check map borders\n"));
			else if ((map[j][0] != ' ' && map[j][0] != '1') || (map[j][strlen(map[j]) - 2] != '1' && map[j][strlen(map[j]) - 2] != ' '))
			 	exit(printf("check map borders\n"));
			i++;
		}
		i = 0;
		j++;
	}
	printf("asd\n");
	ft_check_maps2(map);
}

int		ft_max_x(char **map)
{
	int i = 0;
	int size = 0;
	int max = 0;
	while(map[i])
	{
		while(map[i][size])
			size++;
		if (size > max)
			max = size;
		size = 0;
		i++;
	}
	return (max);
}


void	ft_check_maps1(char **str)
{
	int i = 0;
	int j = 0;
	while(str[j])
	{
		i = 0;
		while(str[j][i])
		{
			if (str[j][i] == '0')
			{
				if (str[j][i - 1] == ' ' || str[j][i + 1] == ' ')
					exit(printf("boşluk hatası\n"));
			}
			i++;
		}
		j++;
	}
}

void	ft_check_player(char **map, int i, int j, t_game *mlx)
{
	int counter = 0;
	while(map[j])
	{
		i = 0;
		while(map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'W' || map[j][i] == 'S' || map[j][i] == 'E')
			{
				if (map[j][i - 1] == ' ' || map[j][i + 1] == ' ' || map[j + 1][i] == ' ' || map[j - 1][i] == ' ' )
					exit(printf("player error"));
				if (map[j][i] == 'N')
					mlx->angle = 90.0;
				else if (map[j][i] == 'W')
					mlx->angle = 180.0;
				else if (map[j][i] == 'E')
					mlx->angle = 0.0;
				else if (map[j][i] == 'S')
					mlx->angle = 270.0;
				counter++;
				mlx->character_x = (double)i;
				mlx->character_y = (double)j;
				mlx->map_player_x = (double)(i * mlx->img_pixel);
				mlx->map_player_y = (double)(j * mlx->img_pixel);
				map[j][i] = '0';
				if (counter > 1)
					exit(printf("player counter error"));
			}
			i++;
		}
		j++;
	}
	if(counter == 0)
		exit(printf("player error"));
}

void	check_cub_file(t_game	*mlx)
{
	int map_max_x;

	map_max_x = 0;
	ft_check_directions(mlx->directions); //  yönler ve yanlarindakı dosyalarin açılabilirlik kontrolü
	ft_check_colors(mlx->floor_ceil); // renk kodları 0 ile 255 arasında mı kontol et
	// ft_check_borders(mlx->map); // sınırlarda açıklık var mı kontrol
	ft_check_player(mlx->map, 0, 0, mlx);
	map_max_x = ft_max_x(mlx->map);
	ft_check_maps(mlx->map, map_max_x);///map kontrolu
	ft_check_maps1(mlx->map);
}

char	**mapcontrol(char *av, t_game *mlx)
{
	int roro[5] = {-1, -1, -1, -1, -1};
	char	*line;
    char	**map;
    roro[0] = open(av, O_RDONLY);
    if (roro[0] < 0)
        exit(0);

    mlx->directions = malloc(sizeof(char *) * 5);
    mlx->floor_ceil = malloc(sizeof(char *) * 3);
    mlx->map = malloc(sizeof(char *) * ft_max_y(mlx->path));


	int temp = find_height(mlx->path);
    while (++roro[1] < temp)
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
	mlx->directions[++roro[2]] = 0;
	mlx->map[++roro[3]] = 0;
	mlx->floor_ceil[++roro[4]] = 0;
	check_cub_file(mlx);
    close(roro[0]);
    return (mlx->map);
}
