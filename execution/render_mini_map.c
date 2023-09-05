/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:47:08 by aalami            #+#    #+#             */
/*   Updated: 2023/09/05 21:58:47 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	draw_minimap_elm(t_mlx *mlx, int elm, int i, int j)
{
	float	x;
	float	y;
	int		color;

	y = 0;
	if (elm == 0)
		color = 0xFFFFFF;
	else
		color = 0x000000;
	while (y < TILE_SIZE)
	{
		x = -1;
		while (++x < TILE_SIZE)
			my_mlx_pixel_put(mlx, MAP_SCALE * (x + j * TILE_SIZE), MAP_SCALE
				* (y + i * TILE_SIZE), color);
		y++;
	}
}

void	draw_map_img(char **map, t_mlx *mlx)
{
	float	y;
	int		i;
	int		j;
	int		h;
	int		w;

	i = 0;
	j = 0;
	h = get_rows(map);
	w = get_columns(map);

	while (i < h )
	{
		j = 0;
		while (j < w )
		{
			y = 0;
			if (map[i][j] == '1')
				draw_minimap_elm(mlx, 1, i, j);
			else if (map[i][j] == '0' \
			|| map[i][j] == 'N' || map[i][j] == 'S' \
			|| map[i][j] == 'E' || map[i][j] == 'W')
				draw_minimap_elm(mlx, 0, i, j);
			j++;
		}
		i++;
	}
}

int	draw_player(t_mlx *mlx)
{
	my_mlx_pixel_put(mlx, MAP_SCALE * mlx->player.x, MAP_SCALE * mlx->player.y,
		0xF93308);
	return (0);
}
