/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:00:25 by aalami            #+#    #+#             */
/*   Updated: 2023/08/08 21:05:52 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>

void	get_horizontal_intersect(t_mlx *mlx, int i)
{
	double y_intersect;
	double x_intersect;
	double y_step;
	double x_step;
	
	y_step = TILE_SIZE;
	x_step = y_step / tan(mlx->player.rotat_angle);
	y_intersect = floor(mlx->player.y / TILE_SIZE);
	x_intersect = (mlx->player.x + ((mlx->player.y - y_intersect) / tan(mlx->player.rotat_angle))) / TILE_SIZE;
	
	while (mlx->map[(int)y_intersect][(int)x_intersect] != '1')
	{
		y_intersect += ( y_step) / TILE_SIZE;
		x_intersect += (x_step) / TILE_SIZE;
	}
    mlx->rays[i].h_intersec_x = x_intersect * TILE_SIZE;
    mlx->rays[i].h_intersec_y = y_intersect * TILE_SIZE;
	double dx = (x_intersect * TILE_SIZE) - mlx->player.x;
	double dy = (y_intersect * TILE_SIZE) - mlx->player.y;
	mlx->rays[i].dis =  sqrt(pow(dx, 2) + pow(dy, 2));
}
void    get_vertical_intersect(t_mlx *mlx, int i)
{
    double y_intersect;
	double x_intersect;
	double y_step;
	double x_step;
    x_step = TILE_SIZE;
	y_step = x_step * tan(mlx->player.rotat_angle);
	x_intersect = floor(mlx->player.x / TILE_SIZE);
	y_intersect = (mlx->player.y + ((mlx->player.x - x_intersect) / tan(mlx->player.rotat_angle))) / TILE_SIZE;
    while (mlx->map[(int)y_intersect][(int)x_intersect] != '1')
	{
		y_intersect += ( y_step) / TILE_SIZE;
		x_intersect += (x_step) / TILE_SIZE;
	}
    printf("55\n");
     mlx->rays[i].v_intersec_x = x_intersect * TILE_SIZE;
    mlx->rays[i].v_intersec_y = y_intersect * TILE_SIZE;
	double dx = (x_intersect * TILE_SIZE) - mlx->player.x;
	double dy = (y_intersect * TILE_SIZE) - mlx->player.y;
    if (sqrt(pow(dx, 2) + pow(dy, 2)) < mlx->rays[i].dis)
        mlx->rays[i].dis = sqrt(pow(dx, 2) + pow(dy, 2));
}
void    get_intersect_and_draw(t_mlx *mlx, int i)
{
    get_horizontal_intersect(mlx, i);
    // get_vertical_intersect(mlx, i);
    
    draw_ray_line(mlx, mlx->rays[i].ray_angle, mlx->player.x + 1, mlx->player.y + 1, i);
}