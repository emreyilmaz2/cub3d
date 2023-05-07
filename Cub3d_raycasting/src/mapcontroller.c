/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcontroller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:07:21 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/05 14:57:38 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	isargtrue(t_cub3d *img)
{
	int	len;

	len = ft_strlen2(img->map_input[1]);
	if (img->map_input[1][len - 1] != 'b' &&
		img->map_input[1][len - 2] != 'u' &&
		img->map_input[1][len - 3] != 'c' &&
		img->map_input[1][len - 4] != '.')
	{
		write(2, "\033[1;31mWrong map format!\n\033[0m", 30);
		exit(1);
	}
}

void	mapcheck(t_cub3d *img)
{
	img->uz_y = -1;
	img->l_iter = 0;
	int (fd_map) = open(img->map_input[1], O_RDONLY);
	if (fd_map < 0)
		exit_func2("\033[1;31mFile could not be opened!\n\033[0m");
	img->map = malloc((sizeof(char *)) * 1024);
	while (++(img->uz_y) <= line_length(img))
	{
		img->line = get_next_line(fd_map);
		if (!img->line)
			break ;
		if (!img->texture_bool)
			mapcheck2(img->line, img);
		else if (!img->map_bool
			&& img->texture_bool && img->line[0] != '\n')
		{
			img->map[img->l_iter] = ft_strdup(img->line);
			write(1, img->map[img->l_iter], ft_strlen(img->map[img->l_iter]));
			img->l_iter++;
		}
		free(img->line);
	}
	close(fd_map);
	mapcontroller2(img, img->l_iter);
}

void	mapcheck2(char *words, t_cub3d *img)
{
	int	fd;
	int	i;

	i = 0;
	img->split = ft_split(words, ' ');
	if (!strcmp(img->split[0], "NO") || !strcmp(img->split[0], "SO")
		|| !strcmp(img->split[0], "WE") || !strcmp(img->split[0], "EA"))
	{
		img->split[1] = clear_endstr(img->split[1]);
		fd = open(img->split[1], O_RDONLY);
		if (fd < 0 || isargtrue2(img->split[1]))
			exit_split_func(img->split, img);
		split_comp(img->split, img);
	}
	else if (!strcmp(img->split[0], "F") || !strcmp(img->split[0], "C"))
	{
		ft_color(img);
		double_free_split(img->split, img->ut_color);
	}
	else
	{
		free(img->split[0]);
		free(img->split);
	}
	texture_check(img);
}

void	mapcheck3(char *words, t_cub3d *img)
{
	int (j) = 0;
	while (words[j] && words[j] != '\n')
	{
		if (words[j] != '1' && words[j] != '0' && words[j] != 'N'
			&& words[j] != 'S' && words[j] != 'E' && words[j] != 'W'
			&& words[j] != '\n' && words[j] != ' ' && words[j] != 32)
		{
			exit_func("hatali bir yer var\n", img);
		}
		else
		{
			if (words[j] == 'N')
				img->n_timer++;
			else if (words[j] == 'S')
				img->s_timer++;
			else if (words[j] == 'E')
				img->e_timer++;
			else if (words[j] == 'W')
				img->w_timer++;
		}
		if (img->n_timer + img->s_timer + img->e_timer + img->w_timer > 1)
			exit_func("\nW, S, E, or N not occured once\n", img);
		j++;
	}
}

void	realmapcheck(int i, t_cub3d *img)
{
	int (j) = 0;
	while (img->map[i])
	{
		j = -1;
		while (img->map[i][++j])
		{
			if ((img->map[i][j] == 'N' || img->map[i][j] == 'S'
				|| img->map[i][j] == 'W' || img->map[i][j] == 'E')
				&& (img->map[i][j - 1] <= 32 || img->map[i][j + 1] <= 32))
				exit_func("Player yanı hatası\n", img);
			if (img->map[i][j] == ' ' && img->map[i][j] == '\t')
				j++;
			else if (img->map[i][j] == '0' && (!img->map[i - 1]
					|| !img->map[i - 1][j] || img->map[i - 1][j] <= 32))
				exit_func("Ilk satir hatası\n", img);
			else if (img->map[i][0] != '1' && img->map[i][0] > 32)
				exit_func("Ilk sutun 0 hatasi\n", img);
			else if (img->map[i][j + 1] == '\n' && img->map[i][j] == '0')
				exit_func("Son sutun 0 hatasi\n", img);
			else if (img->map[i][j] == '0' && (i == img->max_map_height - 1
					|| (img->map[i + 1][j] && img->map[i + 1][j] <= 32)))
				exit_func("Son satir 0 hatasi\n", img);
		}
		i++;
	}
}
