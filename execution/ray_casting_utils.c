/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:12:58 by aalami            #+#    #+#             */
/*   Updated: 2023/08/24 14:45:14 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	draw_pixels_line(t_mlx *mlx, float dx, float dy)
{
	int		step;
	float	x1;
	float	y1;
	float	x_inc;
	float	y_inc;

	x1 = mlx->player.x;
	y1 = mlx->player.y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	while (step)
	{
		my_mlx_pixel_put(mlx, MAP_SCALE * x1, MAP_SCALE * y1, 0x00FF42);
		x1 += x_inc;
		y1 += y_inc;
		step--;
	}
}

void	draw_ray_line(t_mlx *mlx, float x1, float y1, int j)
{
	float	dx;
	float	dy;
	float	x2;
	float	y2;

	x2 = x1 + cos(mlx->rays[j].ray_angle) * mlx->rays[j].dis;
	y2 = y1 + sin(mlx->rays[j].ray_angle) * mlx->rays[j].dis;
	dx = x2 - mlx->player.x;
	dy = y2 - mlx->player.y;
	draw_pixels_line(mlx, dx, dy);
}
