/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:45:30 by adardour          #+#    #+#             */
/*   Updated: 2023/09/01 17:53:45 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include "../include/parsing.h"

int	parsing(char **argv, int reached_map, int fd, t_data *data)
{
	if (!put_data(data, fd, &reached_map) || reached_map < 6)
	{
		printf(DISPLAY_ERROR1);
		exit (1);
	}
	else if (!check_rgbs(data->ceiling, data->floor))
		return (printf(DISPLAY_ERROR2), 1);
	parse_map(data, reached_map, argv[1]);
	check_symbols(data->map_represent);
	complete_the_map(get_longest_length(data->map_represent), data);
	if (!colors(data))
	{
		printf("error\n");
		exit(1);
	}
	open_texture(data->texture.no, \
	data->texture.so, data->texture.we, \
	data->texture.ea);
	if (!check_map(data->map_represent) || !check_(data->map_represent))
	{
		free_things(data->map_represent);
		free_data(data);
		return (1);
	}
	return (0);
}
