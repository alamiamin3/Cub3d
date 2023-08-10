/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:10:27 by aalami            #+#    #+#             */
/*   Updated: 2023/08/10 22:43:46 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_wall(t_mlx *mlx, double angle, double x1, double y1, int j)
{
	double dx;
	double dy;
	double x2;
	double y2;
	
	int step;
	double x_inc;
	double y_inc;
	int i;

	i = 0;
	x2 = x1 + cos(angle) * mlx->rays[j].dis;
	y2 = y1 + sin(angle) * mlx->rays[j].dis;
	dx = x2 - mlx->player.x;
	dy = y2 - mlx->player.y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	while (i < step)
	{
		my_mlx_pixel_put(mlx,x1, y1, 0xF93308);
		x1 += x_inc;
		y1 += y_inc;
		i++;
	}
}
void    render_walls(t_mlx *mlx)
{
    double  proj_wall;
    double  proj_dis;
    int i;

    i = 0;
    proj_dis = (mlx->win_w / 2) / tan(FOV / 2);
    while (i < mlx->win_w)
    {
        proj_wall = proj_dis * (TILE_SIZE / mlx->rays[i].dis);
        
        i++;
    }
}