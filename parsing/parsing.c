/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:45:30 by adardour          #+#    #+#             */
/*   Updated: 2023/09/07 16:35:02 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include "../include/parsing.h"

int validate_element(char **argv, int reached_map,t_data *data)
{
	char	*line;
	int		fd;
	static int flags;
	char **spliting;
	int i;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("");
		return (0);
	}
	i = 0;
	line = get_next_line(fd);
	while (line != NULL && i < reached_map)
	{
		if (ft_strcmp(line, "\n"))
		{
			spliting = ft_split(line, ' ');
			if (ft_strcmp(spliting[0], "NO") &&
			ft_strcmp(spliting[0], "SO") &&
			ft_strcmp(spliting[0], "WE") &&
			ft_strcmp(spliting[0], "EA") && 
			ft_strcmp(spliting[0], "C") &&
			ft_strcmp(spliting[0], "F"))
			{
				free(line);
				free_things(spliting);
				return (0);
			}
			else 
				flags++;
			free_things(spliting);
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	if (flags > 6)
	{
		free(line);
		return (0);
	}
	data->start_map = ft_strdup(line);
	free(line);
	return (1);
}

int	parsing(char **argv, int reached_map, int fd, t_data *data)
{
	if (!put_data(data, fd, &reached_map))
	{
		printf(DISPLAY_ERROR1);
		close(fd);
		exit (1);
	}
	else if (!validate_element(argv, reached_map, data))
		return (1);
	else if (!check_rgbs(data->ceiling, data->floor))
		return (printf(DISPLAY_ERROR2), 1);
	parse_map(data, reached_map, argv[1]);
	if (!check_symbols(data->map_represent))
		exit(1);
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
