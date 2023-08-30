/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:48:46 by adardour          #+#    #+#             */
/*   Updated: 2023/08/29 20:23:54 by adardour         ###   ########.fr       */
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

int	check_wall(t_mlx *mlx)
{
	int		pos_x;
	int		pos_y;

	if (mlx->player.walk_direction != 0)
	{
		pos_x = (mlx->player.x + ((cos(mlx->player.rotat_angle) \
		* (mlx->player.mov_speed * 5)) \
		* mlx->player.walk_direction)) / TILE_SIZE;
		pos_y = (mlx->player.y + ((sin(mlx->player.rotat_angle) \
		* (mlx->player.mov_speed * 5)) \
		* mlx->player.walk_direction)) / TILE_SIZE;
		if (mlx->map[pos_y][pos_x] == '1')
			return (0);
	}
	return (1);
}

int	check_path(char *path, t_mlx *mlx)
{
	int		w;
	int		h;
	void	*img;

	img = mlx_xpm_file_to_image(mlx->mlx_init, path, &w, &h);
	if (!img)
		return (0);
	return (1);
}

int	is_empty(t_mlx *mlx)
{
	char	*path;
	int		i;

	i = -1;
	while (++i < 4)
	{
		if (i == 0)
			path = mlx->data->texture.ea;
		else if (i == 1)
			path = mlx->data->texture.so;
		else if (i == 2)
			path = mlx->data->texture.no;
		else if (i == 3)
			path = mlx->data->texture.we;
		if (!check_path(path, mlx))
			return (free(path), 1);
		else
			free(path);
	}
	return (0);
}
