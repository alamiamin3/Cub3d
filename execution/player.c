/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:25:09 by aalami            #+#    #+#             */
/*   Updated: 2023/08/30 12:37:14 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	get_rotation(char angle)
{
	if (angle == 'N')
		return (-90);
	else if (angle == 'S')
		return (90);
	else if (angle == 'E')
		return (0);
	return (180);
}

void	init_player(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (mlx->data->map_represent[++i])
	{
		j = -1;
		while (mlx->data->map_represent[i][++j] != '\0')
		{
			if (mlx->data->map_represent[i][j] == 'N' \
			|| mlx->data->map_represent[i][j] == 'S' \
			|| mlx->data->map_represent[i][j] == 'E' \
			|| mlx->data->map_represent[i][j] == 'W')
			{
				mlx->angle = mlx->data->map_represent[i][j];
				break ;
			}
		}
	}
	get_player_pos(mlx);
	mlx->player.turn_direction = 0;
	mlx->player.walk_direction = 0;
	mlx->player.rotat_angle = get_rotation(mlx->angle) * (PI / 180);
	mlx->player.rot_speed = 0.015;
	mlx->player.mov_speed = 4.5;
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
