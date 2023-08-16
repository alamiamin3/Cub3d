/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:49:16 by aalami            #+#    #+#             */
/*   Updated: 2023/08/16 23:42:37 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include <mlx.h>
#include <math.h>
#include <string.h>
#define TILE_SIZE 64
#define MAP_SCALE 0.2
#define PI 3.141592
#define FOV 1.02

typedef struct s_ray
{
	float	ray_angle;
	float	h_intersec_x;
	float	h_intersec_y;
	float	hit_x;
	float	hit_y;
	float	v_intersec_x;
	float	v_intersec_y;
	float	dis;
	int	f_l;
	int	f_r;
	int	f_u;
	int	f_d;
	float top_wall;
	float bot_wall;
	int	wall_height;
	int hit_v;
	int hit_h;
}	t_ray;
typedef struct s_map
{
    int	map_h;
    int	map_w;
}	t_map;
typedef struct s_img
{
	void	*img_ptr;
	char	*data;
	int	size;
	int	endian;
	int	bpp;
}	t_img;

typedef	struct  s_player
{
	float	x;
	float y;
	int turn_direction;  // 0 (default)  1 (right) -1 (left)
	int walk_direction;  // 0 (default)  1 (up)    -1 (down)
	float rotat_angle;
	float mov_speed; //how many pixel per frame to increase or decrease
	float	rot_speed; //how many degrees per frame to increase or decreaase
	
}	t_player;

typedef	struct  s_texture
{
	t_img	img;
	int	h;
	int	w;
	int	text_offset;
	
}	t_texture;

typedef	struct s_mlx
{
	void	*mlx_init;
	void	*mlx_win;
	int	win_h;
	int	win_w;
	char **map;
	t_img	img;
	t_img	m_map;
	t_player player;
	t_ray	*rays;
	t_texture	texture;
	t_texture	texture_v;
	int	*text_arr;
	int	*text_v_arr;
}	t_mlx;


typedef struct s_game
{
	t_mlx	*mlx;
	char	**map;
	t_player player;
	
}	t_game;

void    get_intersect_and_draw(t_mlx *mlx, int i);
void	get_horizontal_intersect(t_mlx *mlx, int i);
void	get_vertical_intersect(t_mlx *mlx, int i);
void	draw_line(t_mlx *mlx, float angle, float x1, float y1);
void	draw_ray_line(t_mlx *mlx, float angle, float x1, float y1, int j);
void    render_projection(t_mlx *mlx);
void	draw_project(t_mlx *mlx, float x1, float y1, float wall_height, int color);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	render_walls(t_mlx *mlx);
void	render_ceiling(t_mlx *mlx);
void	render_floor(t_mlx *mlx);
void	walk_player(t_mlx *mlx);
int	rotate_player(t_mlx *mlx);
int	check_wall(t_mlx *mlx);
#endif