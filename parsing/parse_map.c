/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:48:32 by adardour          #+#    #+#             */
/*   Updated: 2023/09/07 16:29:28 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	fill_array_2d(t_data *data, int count, char *start_map, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDWR);
	if (fd == -1)
		exit(1);
	line = get_next_line(fd);
	while (ft_strcmp(line, start_map))
	{
		free(line);
		line = get_next_line(fd);
	}
	data->map_represent = malloc((sizeof(char *) * count) + 1);
	if (!data->map_represent)
	{
		perror("");
		exit(1);
	}
	free(line);
	if (fill(fd, data, count, start_map))
		return (0);
	close(fd);
	return (1);
}

int	get_number_of_lines(char *start, char *path)
{
	int		count;
	char	*line;

	int fd;
	count = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(1);
	line = get_next_line(fd);
	while (line && ft_strcmp(line, start))
	{
		free(line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

int	check_spaces_line(char *line)
{
	int	i;

	i = 0;
	while ((size_t)i < ft_strlen(line) - 1)
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	parse_map(t_data *data, int reached_map, char *path)
{
	int fd;
	char *line;
	char	*start_map;
	int		count;
	fd = open(path, O_RDWR, 0777);
	if (fd == -1)
		exit(1);
	start_map = ft_strdup(data->start_map);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	count = get_number_of_lines(start_map, path);
	close(fd);
	if (fill_array_2d(data, count, start_map, path))
	{
		free(start_map);
		return (0);
	}
	free(start_map);
	return (1);
}
