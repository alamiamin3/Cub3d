/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:26:54 by aalami            #+#    #+#             */
/*   Updated: 2023/08/19 14:40:44 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_project(t_mlx *mlx, float x1, float y1, float y2,
		int color)
{
	float	step;
	float	dy;
	float	y_inc;
	int		i;

	i = 0;
	dy = y2 - y1;
	step = fabs(dy);
	y_inc = dy / step;
	while (i < (int)step)
	{
		my_mlx_pixel_put(mlx, x1, y1, color);
		y1 += y_inc;
		i++;
	}
}

void	render_ceiling(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->win_w)
	{
		draw_project(mlx, i, 0, mlx->rays[i].top_wall, 0x73BEFF);
		i++;
	}
}

void	render_floor(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->win_w)
	{
		draw_project(mlx, i, mlx->rays[i].bot_wall, mlx->win_h, 0x5B595B);
		i++;
	}
}
