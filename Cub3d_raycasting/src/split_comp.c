/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_comp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:07:42 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/04 18:07:43 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	double_free_split(char **split1, char **split2)
{
	int (i) = 0;
	while (split1[i])
		free(split1[i++]);
	free(split1);
	i = 0;
	while (split2[i])
		free(split2[i++]);
	free(split2);
}

void	free_split(char **split)
{
	int (i) = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	split_comp(char **split, t_cub3d *img)
{
	if (strcmp(split[0], "NO") == 0)
	{
		img->no_path = ft_strdup(split[1]);
		img->no = 1;
		free_split(split);
	}
	else if (strcmp(split[0], "SO") == 0)
	{
		img->so_path = ft_strdup(split[1]);
		img->so = 1;
		free_split(split);
	}
	else if (strcmp(split[0], "WE") == 0)
	{
		img->we_path = ft_strdup(split[1]);
		img->we = 1;
		free_split(split);
	}
	else if (strcmp(split[0], "EA") == 0)
	{
		img->ea_path = ft_strdup(split[1]);
		img->ea = 1;
		free_split(split);
	}
}
