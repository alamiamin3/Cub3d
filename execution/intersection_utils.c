/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:22:10 by aalami            #+#    #+#             */
/*   Updated: 2023/09/05 18:10:56 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	is_boundries_hited(t_mlx *mlx, float x_inter, float y_inter)
{
	int	height;
	int	width;

	height = get_rows(mlx->map);
	width = get_columns(mlx->map);
	if ((int)y_inter / TILE_SIZE < 0 || (int)y_inter / TILE_SIZE >= height)
		return (1);
	if ((int)x_inter / TILE_SIZE < 0 || (int)x_inter / TILE_SIZE >= width)
		return (1);
	else
		return (0);
}

int	is_wall_hitted(t_mlx *mlx, float x_inter, float y_inter, int i)
{
	int	map_x;
	int	map_y;

	if (mlx->rays[i].inter == 0)
	{
		if (mlx->rays[i].f_u)
			y_inter -= 1;
		else
			y_inter += 1;
	}
	else
	{
		if (mlx->rays[i].f_l)
			x_inter -= 1;
		else
			x_inter += 1;
	}
	map_x = (int)x_inter / TILE_SIZE;
	map_y = (int)y_inter / TILE_SIZE;
	if (mlx->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	get_first_intersection(t_mlx *mlx, float *xi, float *yi, int i)
{
	if (mlx->rays[i].inter == 0)
	{
		*yi = floor(mlx->player.y / TILE_SIZE) * TILE_SIZE;
		if (mlx->rays[i].f_d)
			*yi += TILE_SIZE;
		*xi = mlx->player.x + ((*yi - mlx->player.y)
				/ tan(mlx->rays[i].ray_angle));
	}
	else
	{
		*xi = floor(mlx->player.x / TILE_SIZE) * TILE_SIZE;
		if (mlx->rays[i].f_r)
			*xi += TILE_SIZE;
		*yi = (mlx->player.y + ((*xi - mlx->player.x)
					* tan(mlx->rays[i].ray_angle)));
	}
}

void	save_distance(t_mlx *mlx, float xi, float yi, int i)
{
	float	dx;
	float	dy;

	dy = yi - mlx->player.y;
	dx = xi - mlx->player.x;
	if (mlx->rays[i].inter == 0)
	{
		mlx->rays[i].hit_x = xi;
		mlx->rays[i].hit_y = yi;
		mlx->rays[i].dis = sqrt(dx * dx + dy * dy);
		mlx->rays[i].hit_h = 1;
		mlx->rays[i].hit_v = 0;
	}
	else
	{
		if (sqrt(dx * dx + dy * dy) < mlx->rays[i].dis)
		{
			mlx->rays[i].hit_v = 1;
			mlx->rays[i].hit_h = 0;
			mlx->rays[i].dis = sqrt(dx * dx + dy * dy);
			mlx->rays[i].hit_x = xi;
			mlx->rays[i].hit_y = yi;
		}
	}
}
