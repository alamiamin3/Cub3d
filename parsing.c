/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:45:30 by adardour          #+#    #+#             */
/*   Updated: 2023/08/30 12:35:51 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub.h"
#include "./include/parsing.h"

int	parsing(char **argv, int reached_map, int fd, t_mlx *mlx)
{
	if (!put_data(mlx->data, fd, &reached_map) || reached_map < 6)
		return (printf(DISPLAY_ERROR1), 1);
	if (!check_rgbs(mlx->data->ceiling, mlx->data->floor))
		return (printf(DISPLAY_ERROR2), 1);
	close(fd); 
	parse_map(mlx->data, reached_map, argv[1]);
	check_symbols(mlx->data->map_represent);
	complete_the_map(get_longest_length(mlx->data->map_represent), mlx->data);
	colors(mlx->data);
	open_texture(mlx->data->texture.no, \
	mlx->data->texture.so, mlx->data->texture.we, \
	mlx->data->texture.ea);
	if (!check_map(mlx->data->map_represent) \
	|| is_empty(mlx) || !check_(mlx->data->map_represent))
	{
		printf("some error in map or textures\n");
		free(mlx);
		exit(1);
	}
	return (0);
}
