/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:49:16 by aalami            #+#    #+#             */
/*   Updated: 2023/09/05 18:26:31 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define TILE_SIZE 64
# define MAP_SCALE 0.15
# define PI 3.141592
# define FOV 1.02
# define ARR_LEFT 123
# define ARR_RIGHT 124
# define KEY_UP 13
# define KEY_DOWN 1
# define KEY_RIGHT 2
# define KEY_LEFT 0
# define KEY_EXIT 53
# include "./parsing.h"

typedef struct s_ray
{
	int			inter;
	float		ray_angle;
	float		h_intersec_x;
	float		h_intersec_y;
	float		hit_x;
	float		hit_y;
	float		v_intersec_x;
	float		v_intersec_y;
	float		dis;
	int			f_l;
	int			f_r;
	int			f_u;
	int			f_d;
	float		top_wall;
	float		bot_wall;
	int			wall_height;
	int			hit_v;
	int			hit_h;
}				t_ray;

typedef struct s_map
{
	int			map_h;
	int			map_w;
}				t_map;

typedef struct s_img
{
	void		*img_ptr;
	char		*data;
	int			size;
	int			endian;
	int			bpp;
}				t_img;

typedef struct s_player
{
	float		x;
	float		y;
	int			turn_direction;
	int			walk_ud;
	int			walk_rl;
	float		rotat_angle;
	float		mov_speed;
	float		rot_speed;
}				t_player;

typedef struct s_texture
{
	t_img		img;
	int			h;
	int			w;
	int			text_offset;
}				t_texture;

typedef struct t_axes
{
	float		x1;
	float		y1;
	float		y2;
}				t_axes;

typedef struct s_mlx
{
	void		*mlx_init;
	void		*mlx_win;
	int			win_h;
	int			win_w;
	char		**map;
	char		angle;
	t_img		img;
	t_img		m_map;
	t_player	player;
	t_ray		*rays;
	t_texture	text_n;
	t_texture	text_s;
	t_texture	text_e;
	t_texture	text_w;
	int			*text_n_arr;
	int			*text_s_arr;
	int			*text_e_arr;
	int			*text_w_arr;
	t_data		*data;
	t_text		text_ure;
	t_axes		axes;
}				t_mlx;

void			get_intersect_and_draw(t_mlx *mlx, int i);
void			get_horizontal_intersect(t_mlx *mlx, int i);
void			get_vertical_intersect(t_mlx *mlx, int i);
void			draw_ray_line(t_mlx *mlx, float x1, float y1, int j);
void			render_projection(t_mlx *mlx);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void			render_walls(t_mlx *mlx, int i);
void			render_ceiling(t_mlx *mlx);
void			render_floor(t_mlx *mlx);
void			walk_player(t_mlx *mlx);
int				rotate_player(t_mlx *mlx);
int				check_wall(t_mlx *mlx);
void			init_rays_dir(t_mlx *mlx);
void			init_player(t_mlx *mlx);
void			get_player_pos(t_mlx *mlx);
int				move_player(int key, t_mlx *mlx);
void			draw_rays(t_mlx *mlx);
void			cast_rays(t_mlx *mlx);
void			define_direction(t_mlx *mlx, int i);
void			normalize_ray_angle(t_mlx *mlx, int i, float ray_angle);
void			draw_map_img(char **map, t_mlx *mlx);
void			draw_minimap_elm(t_mlx *mlx, int elm, int i, int j);
int				draw_player(t_mlx *mlx);
void			draw_pixels_line(t_mlx *mlx, float dx, float dy);
int				is_boundries_hited(t_mlx *mlx, float x_inter, float y_inter);
int				is_wall_hitted(t_mlx *mlx, float x_inter, float y_inter, int i);
void			get_first_intersection(t_mlx *mlx, float *xi, float *yi, int i);
void			save_distance(t_mlx *mlx, float xi, float yi, int i);
void			draw_based_on_direction(t_mlx *mlx, int i, char dir);
int				ft_exit(t_mlx *mlx);
int				check_(char **map);
void			drawing(t_data *data);
int				release(int key, t_mlx *mlx);
int				render_map(t_mlx *mlx);
int				parsing(char **argv, int reached_map, int fd, t_data *data);
void			init(t_data *data);
void			get_player_pos(t_mlx *mlx);
int				get_text_color(char *data, int x_off, int y_off, int s_l);
void			draw_ceiling(t_mlx *mlx, float x1, float y1, float y2);
void			draw_floor(t_mlx *mlx, float x1, float y1, float y2);
void			free_data(t_data *data);
void			handle_textures(t_mlx *mlx);

#endif