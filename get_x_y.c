/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_x_y.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:34:07 by adardour          #+#    #+#             */
/*   Updated: 2023/08/30 12:39:59 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub.h"

void	get_player_pos(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (mlx->data->map_represent[i])
	{
		j = 0;
		while (mlx->data->map_represent[i][j])
		{
			if (mlx->map[i][j] == 'N' \
			|| mlx->map[i][j] == 'S' \
			|| mlx->map[i][j] == 'E' \
			|| mlx->map[i][j] == 'W')
			{
				mlx->player.x = j * TILE_SIZE + TILE_SIZE / 2;
				mlx->player.y = i * TILE_SIZE + TILE_SIZE / 2;
				return ;
			}
			j++;
		}
		i++;
	}
}
