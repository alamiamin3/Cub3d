/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:10:27 by aalami            #+#    #+#             */
/*   Updated: 2023/08/13 22:05:27 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>
#include <stdlib.h>

void	draw_project(t_mlx *mlx, float x1, float y1, float wall_height, int color)
{
	float dx;
	float dy;
	float x2;
	float y2;
	
	float step;
	float x_inc;
	float y_inc;
	int i;

	i = 0;
	x2 = x1 ;
	y2 = wall_height;

	dx = x2 - x1;
	dy = y2 - y1;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	while (i < (int)step)
	{
		my_mlx_pixel_put(mlx, x1, y1, color);
		x1 += x_inc;
		y1 += y_inc;
		i++;
	}
}
void	render_ceiling(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < mlx->win_w)
	{
		draw_project(mlx, i, 0, mlx->rays[i].top_wall, 0xB8F1F4);
		i++;
	}
}
void	render_floor(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < mlx->win_w)
	{
		draw_project(mlx, i, mlx->rays[i].bot_wall - 1, mlx->win_h, 0xBFFFCC);
		i++;
	}
}
int	get_vertical_texture_pixel(t_mlx *mlx)
{
	static int x_t;
	static int y_t;
	char	*dst;
	int	color ;
	
	if (y_t > mlx->texture.img.size)
	{
		y_t = 0;
		x_t ++;
		if (x_t > TILE_SIZE)
			x_t = 0;
	}

		dst = mlx->texture.img.data + y_t * mlx->texture.img.size + x_t * (mlx->texture.img.bpp / 8);
		color = *(unsigned int *)dst;
		y_t ++;
	return (color);
}
void	draw_vertical_texture(t_mlx *mlx, float x1, float y1, float wall_height)
{
	float dx;
	float dy;
	float x2;
	float y2;
	
	float step;
	float x_inc;
	float y_inc;
	int	color;
	int i;

	i = 0;
	x2 = x1 ;
	y2 = wall_height;

	dx = x2 - x1;
	dy = y2 - y1;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	while (i < (int)step)
	{
		color = get_vertical_texture_pixel(mlx);
		my_mlx_pixel_put(mlx, x1, y1, color);
		x1 += x_inc;
		y1 += y_inc;
		i++;
	}
}
void	render_walls(t_mlx *mlx)
{
	int i;
	int color_h;
	int color_v;
	i = 0;
	color_h = 0xFF7800;
	color_v = 0x9A4800;
	while (i < mlx->win_w)
	{
		if (mlx->rays[i].hit_h)
        	draw_project(mlx, i, mlx->rays[i].top_wall, mlx->rays[i].bot_wall, color_h);
		else
		{
			// color_v = get_vertical_texture_pixel(mlx);
			// draw_vertical_texture(mlx, i, mlx->rays[i].top_wall, mlx->rays[i].bot_wall);
        	draw_project(mlx, i, mlx->rays[i].top_wall, mlx->rays[i].bot_wall, color_v);
		}
			
		i++;
	}
}
void    render_projection(t_mlx *mlx)
{
    float  proj_wall;
    float  proj_dis;
	float	top_wall;
	float	bot_wall;
	float	correct_dis;
    int i;

    i = 0;
    proj_dis = (mlx->win_w / 2) / (tan(FOV / 2));
    while (i < mlx->win_w)
    {
		correct_dis = cos(mlx->player.rotat_angle - mlx->rays[i].ray_angle) * mlx->rays[i].dis;
		// printf("dsd %f\n", correct_dis);
        proj_wall = proj_dis * (TILE_SIZE / correct_dis);
		// printf("proj_dis : %f proj_wall : %f ray_dis : %f  , win_h : %d \n \n", proj_dis, proj_wall, mlx->rays[i].dis, mlx->win_h);
		mlx->rays[i].top_wall = (mlx->win_h / 2) - (proj_wall / 2);
		mlx->rays[i].bot_wall = (mlx->win_h / 2) + (proj_wall / 2);
		if (mlx->rays[i].top_wall < 0)
			mlx->rays[i].top_wall = 0;
		if (mlx->rays[i].bot_wall > mlx->win_h)
			mlx->rays[i].bot_wall = mlx->win_h;
		// printf("%f %f\n", mlx->rays[i].top_wall, mlx->rays[i].bot_wall);
        i ++;
    }
	// render_ceiling(mlx);
	// render_floor(mlx);
}