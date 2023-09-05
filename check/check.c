/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:48:46 by adardour          #+#    #+#             */
/*   Updated: 2023/09/05 15:18:33 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include "../include/parsing.h"

void	check_last_line(char **map_represent, int index_last)
{
	int	i;

	i = 0;
	while (map_represent[index_last][i] != '\0')
	{
		if (map_represent[index_last][i] != '.')
		{
			if (map_represent[index_last][i] != '1')
			{
				printf("The map must be closed/surrounded by walls\n");
				free_things(map_represent);
				exit(1);
			}
		}
		i++;
	}
}

int	check_car(char *r, char *g, char *b)
{
	int		i;
	int		check_;

	i = 0;
	check_ = 0;
	while (i < 3)
	{
		if (i == 0)
			check_ += check_color(r);
		else if (i == 1)
			check_ += check_color(g);
		else if (i == 2)
			check_ += check_color(b);
		i++;
	}
	return (check_);
}

void	check_walk(t_mlx *mlx, int *pos_x, int *pos_y)
{
	if (mlx->player.walk_ud == 1 || mlx->player.walk_ud == -1)
	{
		*pos_x = (mlx->player.x + ((cos(mlx->player.rotat_angle) \
		* (mlx->player.mov_speed * 5)) \
		* mlx->player.walk_ud)) / TILE_SIZE;
		*pos_y = (mlx->player.y + ((sin(mlx->player.rotat_angle) \
		* (mlx->player.mov_speed * 5)) \
		* mlx->player.walk_ud)) / TILE_SIZE;
	}
	else
	{
		*pos_x = (mlx->player.x + ((cos(mlx->player.rotat_angle - 1.57) \
		* (mlx->player.mov_speed * 5)) \
		* mlx->player.walk_rl)) / TILE_SIZE;
		*pos_y = (mlx->player.y + ((sin(mlx->player.rotat_angle - 1.57) \
		* (mlx->player.mov_speed * 5)) \
		* mlx->player.walk_rl)) / TILE_SIZE;
	}
}

int	check_wall(t_mlx *mlx)
{
	int		pos_x;
	int		pos_y;

	if (mlx->player.walk_ud != 0 || mlx->player.walk_rl != 0)
	{
		check_walk(mlx, &pos_x, &pos_y);
		if (mlx->map[pos_y][pos_x] == '1')
			return (0);
	}
	return (1);
}
