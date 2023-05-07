/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:45:01 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/05 14:35:08 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "stdbool.h"
# include "stdio.h"
# include "unistd.h"
# include "fcntl.h"
# include "math.h"
# include "../minilibx/mlx.h"
# include "../mlx/mlx.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/source/libft.h"

# define PI 3.141592653
# define DR 0.0174533

# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 720
# define ANGLE_CAMERA 60
# define TAB 48

# define A 0
# define S 1
# define D 2
# define W 13
# define ESC 53
# define L 123
# define R 124
# define BLUE 0x000000FF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define MAGENTA 0x00FF00FF
# define CYAN 0x8000FFFF

typedef struct s_bool
{
	bool	w_check;
	bool	a_check;
	bool	s_check;
	bool	d_check;
	bool	r_check;
	bool	l_check;
	bool	tab_check;
}	t_check;

typedef struct s_mlximg
{
	void	*ptr;
	int		*addr;
	int		bpp;
	int		line_size;
	int		endian;
}	t_mlximg;

typedef struct s_xpm
{
	t_mlximg	img;
	int			width;
	int			height;
}	t_xpm;

typedef struct cub3d
{
	void	*mlx;
	void	*mlx_win;
	t_check	*check;
	char	**map;
	char	**map_input;
	int		*addr_map;
	void	*img_map;
	int		*addr_player;
	void	*img_player;
	int		*addr_ray;
	void	*img_ray;
	int		*addr_game;
	void	*img_game;
	void	*wall;
	void	*floor;
	int		line_length;
	int		bits_per_pixel;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	int		texture_bool;
	int		map_bool;
	int		max_map_width;
	int		max_map_height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		f_color[3];
	int		c_color[3];
	int		f_final;
	int		c_final;
	int		n_timer;
	int		s_timer;
	int		e_timer;
	int		w_timer;
	int		x_kord;
	int		y_kord;
	double	p_x;
	double	p_y;
	int		speed_pixel;
	int		pixel;
	double	speed;
	double	angle;
	double	degree;
	float	angle_x;
	float	angle_y;
	double	_dir_x;
	double	_dir_y;
	int		max_x;
	int		max_y;
	bool	_hith;
	bool	_hitv;
	t_xpm	xpm[4];
	int		xpm_number;
	int		img_loc;
	int		find_pixel;
	double	ray_x;
	double	ray_x_v;
	double	ray_x_h;
	double	ray_y;
	double	ray_y_v;
	double	ray_y_h;
	int		color;
	char	**split;
	char	**ut_color;
	double	newp_x;
	double	newp_y;
	double	new_angle;
	int		uz_y;
	int		l_iter;
	char	*line;
	int		dirx;
	int		diry;
	double	distance_v;
	double	distance_h;
	double	vdy;
	double	vdx;
	double	tmp_x;
	double	tmptwo_x;
	double	tmp_y;
	double	tmptwo_y;
	double	hdy;
	double	hdx;
}	t_cub3d;

int		pushbutton(int keycode, t_cub3d *ptr);
void	isargtrue(t_cub3d *cub3dptr);
int		line_length(t_cub3d *cub3dptr);
void	putpixel(t_cub3d *cub3dptr);
void	mapcheck(t_cub3d *cub3dptr);
void	check_all(t_cub3d *img);
void	free_all(t_cub3d *img);
void	exit_func(char *err, t_cub3d *img);
void	split_comp(char **split, t_cub3d *img);
void	mapcheck2(char *words, t_cub3d *img);
void	mapcheck3(char *words, t_cub3d *img);
void	exit_split_func(char **split, t_cub3d *img);
void	free_split(char **split);
void	exit_double_split_func(char **split, char **color, t_cub3d *img);
char	*clear_endstr(char *str);
int		is_number(char *str);
void	mapdrawcheck(char *words, t_cub3d *img);
void	ismaptrue(char *words, t_cub3d *img);
void	double_free_split(char **split1, char **split2);
void	realmapcheck(int i, t_cub3d *img);
void	my_mlx_pixel_put(t_cub3d *img, int x, int y, int color);
void	my_mlx_pixel_put2(t_cub3d *img);
void	player(t_cub3d *cub3dptr);
void	turnleft(t_cub3d *cub3d);
void	turnup(t_cub3d *cub3d);
void	turnright(t_cub3d *cub3d);
void	turndown(t_cub3d *cub3d);
int		putimage(t_cub3d *img);
void	map_addr(t_cub3d *img);
int		key_press(int keycode, t_cub3d *ptr);
int		key_release(int keycode, t_cub3d *ptr);
void	keycheckforloop(t_cub3d *img);
void	convertangle(char c, t_cub3d *img);
void	angleright(t_cub3d *img);
void	angleleft(t_cub3d *img);
double	distance(double ax, double ay, double bx, double by);
void	my_mlx_pixe_put_angle(t_cub3d *img);
void	pixel_to_player_image_address(t_cub3d *img, int x, int y, int color);
void	pixel_to_ray_image_address(t_cub3d *img, int x, int y, int color);
void	draw3DWalls(t_cub3d *img, double i, int counter, int dir);
void	fill_addr(t_cub3d *img);

void	raycasting(t_cub3d *img, double angle, int ray_counter);
double	ray_vertical(t_cub3d *img, double angle, bool *hit);
double	ray_horizontal(t_cub3d *img, double angle, bool *hit);
int		is_wall_v2(double x, double y, t_cub3d *img);
void	draw_ray(double distance, t_cub3d *img, int ray_count);
int		is_wall(double x, double y, t_cub3d *img);
void	my3d(t_cub3d *img, double distance, int ray_count, t_xpm xpm);
void	exit_func2(char *err);
void	add_xpm(t_cub3d *img);
void	put_transparent(t_cub3d *img);
void	ft_color(t_cub3d *img);
void	mapcontroller2(t_cub3d	*cub3dptr, int i);
void	exit_func3(t_cub3d *img);
int		isargtrue2(char *str);
void	ray_vertical_while(t_cub3d *img, bool *hit, double angle);
void	ray_horizontal_while(t_cub3d *img, bool *hit, double angle);
void	my3d_wall_control(t_cub3d *img, t_xpm xpm);

void	texture_check(t_cub3d *img);
#endif
