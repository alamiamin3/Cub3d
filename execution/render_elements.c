/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:26:54 by aalami            #+#    #+#             */
/*   Updated: 2023/08/30 17:15:35 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	draw_ceiling(t_mlx *mlx, float x1, float y1, float y2)
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
		my_mlx_pixel_put(mlx, x1, y1, mlx->data->ceiling.color);
		y1 += y_inc;
		i++;
	}
}

void	draw_floor(t_mlx *mlx, float x1, float y1, float y2)
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
		my_mlx_pixel_put(mlx, x1, y1, mlx->data->floor.color);
		y1 += y_inc;
		i++;
	}
}

int	get_text_color(char *data, int x_off, int y_off, int s_l)
{
	char	*dst;
	int		color;

	dst = data + (y_off * s_l + x_off * 4);
	color = *(unsigned int *)dst;
	return (color);
}
