/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:48:05 by adardour          #+#    #+#             */
/*   Updated: 2023/08/29 20:10:43 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	put_things(t_data *data, char	**spliting, int flags)
{
	if (spliting[3])
	{
		printf("color not valid\n");
		exit(1);
	}
	if (flags == 0)
	{
		data->floor.g = ft_strdup(spliting[1]);
		data->floor.b = ft_strdup(spliting[2]);
	}
	else
	{
		data->ceiling.g = ft_strdup(spliting[1]);
		data->ceiling.b = ft_strdup(spliting[2]);
	}
}

int	check_identifier(char *line)
{
	char	**spliting;

	spliting = ft_split(line, ' ');
	if (spliting[0] != NULL && spliting[1] != NULL)
	{
		if (spliting[0][0] == 'S' && spliting[0][1] != 'O' \
		&& spliting[0][1] != '\0')
			return (free_things(spliting), 0);
		else if (spliting[0][0] == 'W' && spliting[0][1] != 'E' \
		&& spliting[0][1] != '\0')
			return (free_things(spliting), 0);
		else if (spliting[0][0] == 'E' && spliting[0][1] != 'A' \
		&& spliting[0][1] != '\0')
			return (free_things(spliting), 0);
		else if (spliting[0][0] == 'N' \
		&& spliting[0][1] != 'O' \
		&& spliting[0][1] != '\0')
			return (free_things(spliting), 0);
		else if (spliting[0][0] == 'C' && spliting[0][1] != '\0')
			return (free_things(spliting), 0);
		else if (spliting[0][0] == 'F' && spliting[0][1] != '\0')
			return (free_things(spliting), 0);
	}
	free_things(spliting);
	return (1);
}

void	put_rgb(t_data *data, char *line, char identifier)
{
	char	**spliting;
	char	**dd;

	spliting = ft_split(line, ',');
	if (identifier == 'F')
	{
		if (spliting[0][0] == 'F')
		{
			dd = ft_split(spliting[0], ' ');
			data->floor.r = ft_strdup(dd[1]);
			free_things(dd);
		}
		put_things(data, spliting, 0);
	}
	else if (identifier == 'C')
	{
		if (spliting[0][0] == 'C')
		{
			dd = ft_split(spliting[0], ' ');
			data->ceiling.r = ft_strdup(dd[1]);
			free_things(dd);
		}
		put_things(data, spliting, 1);
	}
	free_things(spliting);
}

void	put(char *line, t_data *data, char i)
{
	char	**spliting;

	spliting = ft_split(line, ' ');
	if (i == 'N')
		data->texture.no = ft_substr(spliting[1], 0, \
		ft_strlen(spliting[1]) - 1);
	if (i == 'S')
		data->texture.so = ft_substr(spliting[1], 0, \
		ft_strlen(spliting[1]) - 1);
	if (i == 'W')
		data->texture.we = ft_substr(spliting[1], 0, \
		ft_strlen(spliting[1]) - 1);
	if (i == 'E')
		data->texture.ea = ft_substr(spliting[1], 0, \
		ft_strlen(spliting[1]) - 1);
	if (i == 'F')
		put_rgb(data, line, 'F');
	if (i == 'C')
		put_rgb(data, line, 'C');
	free_things(spliting);
}

int	put_data(t_data *data, int fd, int *reached_map)
{
	int		flags;
	char	*line;

	flags = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!check_identifier(line))
			return (free(line), 0);
		if (line[0] == 'N' || line[0] == 'S' \
		|| line[0] == 'W' || line[0] == 'E' \
		|| line[0] == 'F' || line[0] == 'C')
		{
			put(line, data, line[0]);
			(*reached_map)++;
		}
		else
			flags++;
		if (*reached_map == 6)
			(*reached_map) += flags;
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}
