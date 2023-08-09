/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:49:16 by aalami            #+#    #+#             */
/*   Updated: 2023/08/09 20:18:43 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include <mlx.h>
#include <math.h>
#define TILE_SIZE 64
#define MINI_SIZE 20
#define FOV 60 * (M_PI / 180)
#define PI 3.141592

typedef struct s_ray
{
	double	ray_angle;
	double	h_intersec_x;
	double	h_intersec_y;
	double	v_intersec_x;
	double	v_intersec_y;
	double	dis;
	int	f_l;
	int	f_r;
	int	f_u;
	int	f_d;
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
	double	x;
	double y;
	int turn_direction;
	int walk_direction;
	double rotat_angle;
	float mov_speed; //how many pixel per frame to increase or decrease
	float	rot_speed; //how many degrees per frame to increase or decreaase
	
}	t_player;
typedef	struct s_mlx
{
	void	*mlx_init;
	void	*mlx_win;
	int	win_h;
	int	win_w;
	char **map;
	t_img	img;
	t_player player;
	t_ray	*rays;
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
void	draw_line(t_mlx *mlx, double angle, double x1, double y1);
void	draw_ray_line(t_mlx *mlx, double angle, double x1, double y1, int j);

#endif