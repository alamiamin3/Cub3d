/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:25:09 by aalami            #+#    #+#             */
/*   Updated: 2023/09/05 15:33:07 by aalami           ###   ########.fr       */
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
	get_player_pos(mlx);
	mlx->player.turn_direction = 0;
	mlx->player.walk_ud = 0;
	mlx->player.walk_rl = 0;
	mlx->player.rotat_angle = get_rotation(mlx->angle) * (PI / 180);
	mlx->player.rot_speed = 0.015;
	mlx->player.mov_speed = 4.5;
}

int	move_player(int key, t_mlx *mlx)
{
	if (key == ARR_LEFT)
		mlx->player.turn_direction = -1;
	if (key == ARR_RIGHT)
		mlx->player.turn_direction = 1;
	if (key == KEY_UP)
		mlx->player.walk_ud = 1;
	if (key == KEY_DOWN)
		mlx->player.walk_ud = -1;
	if (key == KEY_RIGHT)
		mlx->player.walk_rl = -1;
	if (key == KEY_LEFT)
		mlx->player.walk_rl = 1;
	if (key == KEY_EXIT)
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
	if (mlx->player.walk_ud == 1 || mlx->player.walk_ud == -1)
	{
		mlx->player.x += cos(mlx->player.rotat_angle) * mlx->player.mov_speed
			* mlx->player.walk_ud;
		mlx->player.y += sin(mlx->player.rotat_angle) * mlx->player.mov_speed
			* mlx->player.walk_ud;
	}
	else if (mlx->player.walk_rl == 1 || mlx->player.walk_rl == -1)
	{
		mlx->player.x += cos(mlx->player.rotat_angle - 1.57) * \
			mlx->player.mov_speed * mlx->player.walk_rl;
		mlx->player.y += sin(mlx->player.rotat_angle - 1.57) * \
			mlx->player.mov_speed * mlx->player.walk_rl;
	}
}
