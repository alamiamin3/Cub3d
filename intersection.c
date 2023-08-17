/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:00:25 by aalami            #+#    #+#             */
/*   Updated: 2023/08/17 19:26:29 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>

void	get_horizontal_steps(t_mlx *mlx, int i, float *xs, float *ys)
{
	if (mlx->rays[i].f_d)
		*ys = TILE_SIZE;
	else
		*ys = -TILE_SIZE;
	*xs = *ys / (tan(mlx->rays[i].ray_angle));
	if ((mlx->rays[i].f_r && *xs < 0) || (mlx->rays[i].f_l && *xs > 0))
		*xs *= -1;
}

void	get_horizontal_intersect(t_mlx *mlx, int i)
{
	float y_intersect;
	float x_intersect;
	float y_step;
	float x_step;

	mlx->rays[i].inter = 0;
	get_horizontal_steps(mlx, i, &x_step, &y_step);
	get_first_intersection(mlx, &x_intersect, &y_intersect, i);
	while (!is_boundries_hited(mlx, x_intersect, y_intersect) && !is_wall_hitted(mlx, x_intersect, y_intersect, i))
	{
		y_intersect += ( y_step);
		x_intersect += (x_step) ;
	}
   mlx->rays[i].h_intersec_x = x_intersect;
   mlx->rays[i].h_intersec_y = y_intersect;
	save_distance(mlx, x_intersect, y_intersect, i);
}

void	get_vertical_steps(t_mlx *mlx, int i, float *xs, float *ys)
{
	if (mlx->rays[i].f_r)
   	*xs = TILE_SIZE;
	else
   	*xs = -TILE_SIZE;
	*ys = *xs * tan(mlx->rays[i].ray_angle);
	if ((mlx->rays[i].f_d && *ys < 0) || (mlx->rays[i].f_u && *ys > 0))
		*ys *= -1; 

}

void    get_vertical_intersect(t_mlx *mlx, int i)
{
    float y_intersect;
	float x_intersect;
	float y_step;
	float x_step;

	mlx->rays[i].inter = 1;
	get_vertical_steps(mlx, i, &x_step, &y_step);
	get_first_intersection(mlx, &x_intersect, &y_intersect, i);
   while (!is_boundries_hited(mlx, x_intersect, y_intersect) && !is_wall_hitted(mlx, x_intersect, y_intersect, i))
	{
		y_intersect += ( y_step) ;
		x_intersect += (x_step);
	}
    mlx->rays[i].v_intersec_x = x_intersect ;
   mlx->rays[i].v_intersec_y = y_intersect ;
	save_distance(mlx, x_intersect, y_intersect, i);
}
void    get_intersect_and_draw(t_mlx *mlx, int i)
{
	mlx->rays[i].hit_h = 0;
	mlx->rays[i].hit_v = 0;
	get_horizontal_intersect(mlx, i);
	get_vertical_intersect(mlx, i);
}