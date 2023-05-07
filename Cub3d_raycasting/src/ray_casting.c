/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:06:52 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/05 15:33:44 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

/* sin(90) = 1 * (-2) + 1 = -1; yukarıya bakis
dereceden radyana dönüştürür.
Eğer açının cosinüsü pozitif ise,
bu ifade 1 * 2 - 1 = 1 olarak değerlendirilir
Sinüs değeri 0'dan büyükse ışın yukarıyı
gösteriyor demektir ve ((sin(açı * (PI / 180)) > 0) * -2) + 1
ifadesi -1 olarak değerlendirilir.
ray_vertical = dikey
ray_horizontal = yatay
ray_horizontal : verilen bir açı ve konum bilgisine göre,
yatay yönde bir ışın çizerek bu ışının hangi noktalara temas
ettiğini ve temas ettiği ilk duvarın konumunu hesaplar.
*/
void	raycasting(t_cub3d *img, double angle, int ray_counter)
{
	double	original_dist;
	double	distance;

	img->dirx = ((cos(angle * (PI / 180)) > 0) * 2) - 1;
	img->diry = ((sin(angle * (PI / 180)) > 0) * -2) + 1;
	img->_hith = false;
	img->_hitv = false;
	img->distance_v = ray_vertical(img, angle, &img->_hitv);
	img->distance_h = ray_horizontal(img, angle, &img->_hith);
	if (img->distance_v < img->distance_h)
	{
		distance = img->distance_v;
		img->_hith = false;
		img->_hitv = true;
	}
	else
	{
		distance = img->distance_h;
		img->_hith = true;
		img->_hitv = false;
	}
	original_dist = distance;
	distance *= fabs(cos(((img->angle * (180.0 / PI)) - angle) * (PI / 180)));
	draw_ray(distance, img, ray_counter);
}

/* bu durumda karakterin sag kismina isin
gonderilecegi anlamina gelir
cunku floor x sayisindan en kucuk sayiyi dondurur
mesela 3,2 ise 3 dondurur
floor(3,2) - 3 = 0,2 bu da
bulundugu koordinatin hemen sagi demektir
ordan baslar hesaplamaya. Ceil de ise tam tersi
ceil(3,2) -> 4 dondurur bu da 3,2 - 4 = -0,8
tam ters yon demektir hesaplamaya baslanacagi nokta
*/
/* vertical -> dikey
horizontal -> yatay*/
double	ray_vertical(t_cub3d *img, double angle, bool *hit)
{
	double	distance;

	if (img->dirx == -1)
		img->vdx = img->p_x - floor(img->p_x);
	else
		img->vdx = ceil(img->p_x) - img->p_x;
	img->vdy = fabs(tan(angle * (PI / 180)) * img->vdx);
	img->tmp_x = img->vdx * img->dirx;
	img->tmp_y = img->vdy * img->diry;
	ray_vertical_while(img, hit, angle);
	if (*hit == true)
		distance = sqrt((img->tmp_x * img->tmp_x) + (img->tmp_y * img->tmp_y));
	else
		distance = 10000;
	return (distance);
}

double	ray_horizontal(t_cub3d *img, double angle, bool *hit)
{
	double	distance;

	if (img->diry == -1)
		img->hdy = img->p_y - floor(img->p_y);
	else
		img->hdy = ceil(img->p_y) - img->p_y;
	img->hdx = fabs(img->hdy / tan(angle * (PI / 180)));
	img->tmptwo_x = img->hdx * img->dirx;
	img->tmptwo_y = img->hdy * img->dirx;
	ray_horizontal_while(img, hit, angle);
	if (*hit == true)
		distance = sqrt((img->tmptwo_x * img->tmptwo_x) \
			+ (img->tmptwo_y * img->tmptwo_y));
	else
		distance = 10000;
	return (distance);
}

void	draw_ray(double distance, t_cub3d *img, int ray_count)
{
	if (img->_hith == true)
	{
		img->ray_x = img->ray_x_h;
		img->ray_y = img->ray_y_h;
		if (img->diry > 0)
			img->xpm_number = 1;
		else
			img->xpm_number = 0;
	}
	else if (img->_hitv == true)
	{
		img->ray_x = img->ray_x_v;
		img->ray_y = img->ray_y_v;
		if (img->dirx > 0)
			img->xpm_number = 2;
		else
			img->xpm_number = 3;
	}
	my3d(img, distance, ray_count, img->xpm[img->xpm_number]);
}
	/* 0 ve 1 yatay yuzeyler, 2 ve 3 dikey duzeyler
	icin olan xpm dosyasini secioy*/

void	my3d(t_cub3d *img, double distance, int raycount, t_xpm xpm)
{
	double	rate;

	int (i) = 0;
	distance = distance * (double)img->pixel
		* ((double)WINDOW_HEIGHT / (double)WINDOW_WIDTH);
	rate = (((double)WINDOW_HEIGHT / 2.0) / distance) * (double)img->pixel;
	my3d_wall_control(img, xpm);
	img->img_loc = xpm.width * (xpm.height / 2) + img->find_pixel;
	if ((rate >= 4000))
		rate = 4000;
	while (i <= rate && i <= (WINDOW_HEIGHT / 2.0))
	{
		img->color = xpm.img.addr[img->img_loc + xpm.width
			* (int)((double)i * ((double)xpm.width / (double)(rate * 2)))];
		img->addr_game[((WINDOW_HEIGHT / 2) * WINDOW_WIDTH - raycount)
			+ (WINDOW_WIDTH * i)] = img->color;
		img->color = xpm.img.addr[img->img_loc - xpm.width
			* (int)((double)i * ((double)xpm.width / (double)(rate * 2)))];
		img->addr_game[((WINDOW_HEIGHT / 2) * WINDOW_WIDTH - raycount)
			- (WINDOW_WIDTH * i)] = img->color;
		i++;
	}
}
