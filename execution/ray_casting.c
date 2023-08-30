/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:19:50 by aalami            #+#    #+#             */
/*   Updated: 2023/08/28 16:02:14 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	init_rays_dir(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->win_w)
	{
		mlx->rays[i].f_d = 0;
		mlx->rays[i].f_u = 0;
		mlx->rays[i].f_r = 0;
		mlx->rays[i].f_l = 0;
		i++;
	}
}

void	draw_rays(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < mlx->win_w)
		draw_ray_line(mlx, mlx->player.x, mlx->player.y,
			i);
}

void	cast_rays(t_mlx *mlx)
{
	int		i;
	float	ray_angle;

	i = 0;
	ray_angle = mlx->player.rotat_angle - (FOV / 2);
	while (i < mlx->win_w)
	{
		normalize_ray_angle(mlx, i, ray_angle);
		define_direction(mlx, i);
		get_intersect_and_draw(mlx, i);
		ray_angle += FOV / (mlx->win_w);
		i++;
	}
}

void	define_direction(t_mlx *mlx, int i)
{
	if (mlx->rays[i].ray_angle > 0 && mlx->rays[i].ray_angle < PI)
		mlx->rays[i].f_d = 1;
	else
		mlx->rays[i].f_d = 0;
	if (mlx->rays[i].ray_angle > 1.5 * PI || mlx->rays[i].ray_angle < PI / 2)
		mlx->rays[i].f_r = 1;
	else
		mlx->rays[i].f_r = 0;
	mlx->rays[i].f_l = !mlx->rays[i].f_r;
	mlx->rays[i].f_u = !mlx->rays[i].f_d;
}

void	normalize_ray_angle(t_mlx *mlx, int i, float ray_angle)
{
	while (ray_angle < 0)
		ray_angle += 2 * PI;
	while (ray_angle >= 2 * PI)
		ray_angle -= 2 * PI;
	mlx->rays[i].ray_angle = ray_angle;
}
