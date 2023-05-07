/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushbutton.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:06:35 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/05 14:57:07 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	player(t_cub3d *cub3dptr)
{
	cub3dptr->x_kord = 0;
	cub3dptr->y_kord = 0;
	while (cub3dptr->map[cub3dptr->y_kord])
	{
		cub3dptr->x_kord = 0;
		while (cub3dptr->map[cub3dptr->y_kord][cub3dptr->x_kord] != '\0')
		{
			if (cub3dptr->map[cub3dptr->y_kord][cub3dptr->x_kord] == 'N'
				|| cub3dptr->map[cub3dptr->y_kord][cub3dptr->x_kord] == 'S'
				|| cub3dptr->map[cub3dptr->y_kord][cub3dptr->x_kord] == 'E'
				|| cub3dptr->map[cub3dptr->y_kord][cub3dptr->x_kord] == 'W')
			{
				convertangle(cub3dptr->map[cub3dptr->y_kord][cub3dptr->x_kord],
					cub3dptr);
				cub3dptr->p_x = (double)(cub3dptr->x_kord);
				cub3dptr->p_y = (double)(cub3dptr->y_kord);
				cub3dptr->map[cub3dptr->y_kord][cub3dptr->x_kord] = '0';
				return ;
			}
			cub3dptr->x_kord++;
		}
		cub3dptr->y_kord++;
	}
}

void	turnleft(t_cub3d *img)
{
	double	newp_x;
	double	newp_y;

	newp_x = img->p_x - img->speed * sin(img->angle);
	newp_y = img->p_y - img->speed * cos(img->angle);
	if (img->map[(int)newp_y][(int)newp_x] == '0'
			&& img->check->a_check == true)
	{
		img->p_x = newp_x;
		img->p_y = newp_y;
	}
	else if (img->map[(int)newp_y][(int)img->p_x] == '0'
			&& img->check->a_check == true)
		img->p_y = newp_y;
	else if (img->map[(int)img->p_y][(int)newp_x] == '0'
			&& img->check->a_check == true)
		img->p_x = newp_x;
}

void	turnright(t_cub3d *img)
{
	double	newp_x;
	double	newp_y;

	newp_x = img->p_x + img->speed * sin(img->angle);
	newp_y = img->p_y + img->speed * cos(img->angle);
	if (img->map[(int)newp_y][(int)newp_x] == '0'
			&& img->check->d_check == true)
	{
		img->p_x = newp_x;
		img->p_y = newp_y;
	}
	else if (img->map[(int)newp_y][(int)img->p_x] == '0'
			&& img->check->d_check == true)
		img->p_y = newp_y;
	else if (img->map[(int)img->p_y][(int)newp_x] == '0'
			&& img->check->d_check == true)
		img->p_x = newp_x;
}
/* asagidaki kod parcasi W tusuna basildigi zaman
alinacak aksiyonlari gosterir. eger hem x hem y ekseninde
gidilebiliyor ise ilk if diger durumlarda diger kosullar calisir */

void	turnup(t_cub3d *img)
{
	double	newp_x;
	double	newp_y;

	newp_x = img->p_x + img->speed * cos(img->angle);
	newp_y = img->p_y - img->speed * sin(img->angle);
	if (img->map[(int)newp_y][(int)newp_x] == '0'
			&& img->check->w_check == true)
	{
		img->p_x = newp_x;
		img->p_y = newp_y;
	}
	else if (img->map[(int)newp_y][(int)img->p_x] == '0'
			&& img->check->w_check == true)
		img->p_y = newp_y;
	else if (img->map[(int)img->p_y][(int)newp_x] == '0'
			&& img->check->w_check == true)
		img->p_x = newp_x;
}

void	turndown(t_cub3d *img)
{
	double	newp_x;
	double	newp_y;

	newp_x = img->p_x - img->speed * cos(img->angle);
	newp_y = img->p_y + img->speed * sin(img->angle);
	if (img->map[(int)newp_y][(int)newp_x] == '0'
			&& img->check->s_check == true)
	{
		img->p_x = newp_x;
		img->p_y = newp_y;
	}
	else if (img->map[(int)newp_y][(int)img->p_x] == '0'
			&& img->check->s_check == true)
		img->p_y = newp_y;
	else if (img->map[(int)img->p_y][(int)newp_x] == '0'
			&& img->check->s_check == true)
		img->p_x = newp_x;
}
