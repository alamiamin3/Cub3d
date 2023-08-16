/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:10:27 by aalami            #+#    #+#             */
/*   Updated: 2023/08/16 23:42:01 by aalami           ###   ########.fr       */
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
		draw_project(mlx, i, 0, mlx->rays[i].top_wall, 0x73BEFF);
		i++;
	}
}
void	render_floor(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < mlx->win_w)
	{
		draw_project(mlx, i, mlx->rays[i].bot_wall, mlx->win_h, 0x5B595B);
		i++;
	}
}
int	get_vertical_texture_pixel(t_mlx *mlx, float top, float bot)
{
	static int x_t;
	static int check;
	static int y_t;
	char	*dst;
	int	color ;
	
	if (bot - top > TILE_SIZE)
		return (0xD8D8D8);
	if (check > TILE_SIZE)
	{
		y_t = 0;
		check = 0;
		// x_t ++;
		// if (x_t > TILE_SIZE)
		// 	x_t = 0;
	}

		dst = mlx->texture.img.data + y_t + mlx->texture.text_offset * (mlx->texture.img.bpp / 8);
		color = *(unsigned int *)dst;
		// printf("TEXT[X] = %d  | TEXT[Y] = %d \n", mlx->texture.text_offset * (mlx->texture.img.bpp / 8), y_t );
		// if (y_t == mlx->texture.img.size)
		// 	exit (0);
		y_t += mlx->texture.img.size ;
		check ++;
	return (color);
}
void	draw_vertical_texture(t_mlx *mlx, int wall_top,  int wall_bot, int i)
{
	float dx;	
	float dy;
	int	y_off = 0;
	char *dst;
	int color;
	float x_inc;	
	float y_inc;
	int step;
	int j = 0;
	int	y = wall_top;
	step = abs(wall_bot - wall_top);
	// printf("wall top = %d | wall_bot %d |  wall heghit = %d   step = %d\n", wall_top, wall_bot, mlx->rays[i].wall_height, step);
	// exit (0);
	x_inc = 0;
	y_inc = (wall_bot - wall_top) / step ;
	while (j < step)
	{
		int dis_from_top = y + (mlx->rays[i].wall_height / 2) - (mlx->win_h / 2);
		// dst = mlx->texture.img.data + y_off  + mlx->texture.text_offset * 4;
		y_off = dis_from_top * ((float)mlx->texture_v.h / mlx->rays[i].wall_height);
		color = mlx->text_v_arr[y_off * mlx->texture_v.w + mlx->texture_v.text_offset];
		// color = *(int *)dst;
		
		my_mlx_pixel_put(mlx, i, wall_top, color);
		wall_top += 1;
		y++;
		j++;
	}
}
void	draw_horizontal_texture(t_mlx *mlx, int wall_top,  int wall_bot, int i)
{
	float dx;	
	float dy;
	int	y_off = 0;
	char *dst;
	int color;
	float x_inc;	
	float y_inc;
	int step;
	int j = 0;
	int	y = wall_top;
	step = abs(wall_bot - wall_top);
	// printf("wall top = %d | wall_bot %d |  wall heghit = %d   step = %d\n", wall_top, wall_bot, mlx->rays[i].wall_height, step);
	// exit (0);
	x_inc = 0;
	y_inc = (wall_bot - wall_top) / step ;
	while (j < step)
	{
		int dis_from_top = y + (mlx->rays[i].wall_height / 2) - (mlx->win_h / 2);
		// dst = mlx->texture.img.data + y_off  + mlx->texture.text_offset * 4;
		y_off = dis_from_top * ((float)mlx->texture.h  / mlx->rays[i].wall_height);
		color = mlx->text_arr[y_off * mlx->texture.w + mlx->texture.text_offset];
		// color = *(int *)dst;
		
		my_mlx_pixel_put(mlx, i, wall_top, color);
		wall_top += 1;
		y++;
		j++;
	}
}
void	render_walls(t_mlx *mlx)
{ 
	int i;
	int color_h;
	int color_v;
	int b = 0;
	i = 0;
	color_v = 0xFFFFFF;
	color_h = 0xD8D8D8;
	while (i < mlx->win_w)
	{
		if (mlx->rays[i].hit_h)
		{

        	// draw_project(mlx, i, mlx->rays[i].top_wall, mlx->rays[i].bot_wall, color_h);
			// color_h = get_vertical_texture_pixel(mlx);
			mlx->texture.text_offset = (int)fmod(mlx->rays[i].hit_x , TILE_SIZE);
			draw_horizontal_texture(mlx, (int)mlx->rays[i].top_wall, (int)mlx->rays[i].bot_wall, i);
		}
		else
		{
			// color_v = get_vertical_texture_pixel(mlx);
			// draw_vertical_texture(mlx, i, mlx->rays[i].top_wall, mlx->rays[i].bot_wall);
			mlx->texture_v.text_offset = (int)fmod(mlx->rays[i].hit_y ,TILE_SIZE);
			draw_vertical_texture(mlx, (int)mlx->rays[i].top_wall, (int)mlx->rays[i].bot_wall, i);
        	// draw_project(mlx, i, mlx->rays[i].top_wall, mlx->rays[i].bot_wall, color_v);
		}
			// printf("proj = %f\n", mlx->rays[i].bot_wall - mlx->rays[i].top_wall );
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
        proj_wall = proj_dis * (TILE_SIZE / (correct_dis ));
		// printf("proj_dis : %f proj_wall : %f ray_dis : %f  , win_h : %d \n \n", proj_dis, proj_wall, mlx->rays[i].dis, mlx->win_h);
		mlx->rays[i].wall_height = proj_wall;
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