/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:25:09 by aalami            #+#    #+#             */
/*   Updated: 2023/08/20 13:58:03 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_player_pos(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < 14)
	{
		j = 0;
		while (j < 31)
		{
			if (mlx->map[i][j] == 'N')
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

void	init_player(t_mlx *mlx)
{
	get_player_pos(mlx);
	mlx->player.turn_direction = 0;
	mlx->player.walk_direction = 0;
	mlx->player.rotat_angle = 90 * (PI / 180);
	mlx->player.rot_speed = 0.015;
	mlx->player.mov_speed = 5.5;
}

int	move_player(int key, t_mlx *mlx)
{
	if (key == 123)
		mlx->player.turn_direction = -1;
	if (key == 124)
		mlx->player.turn_direction = 1;
	if (key == 13)
		mlx->player.walk_direction = 1;
	if (key == 1)
		mlx->player.walk_direction = -1;
	if (key == 53)
		ft_exit(mlx);
	return (0);
}

int	rotate_player(t_mlx *mlx)
{
	mlx->player.rotat_angle += mlx->player.rot_speed
		* mlx->player.turn_direction;
	while (mlx->player.rotat_angle < 0)
		mlx->player.rotat_angle += 2 * PI;
	while (mlx->player.rotat_angle >= 2 * PI)
		mlx->player.rotat_angle -= 2 * M_PI;
	return (0);
}

void	walk_player(t_mlx *mlx)
{
	mlx->player.x += cos(mlx->player.rotat_angle) * mlx->player.mov_speed
		* mlx->player.walk_direction;
	mlx->player.y += sin(mlx->player.rotat_angle) * mlx->player.mov_speed
		* mlx->player.walk_direction;
}
