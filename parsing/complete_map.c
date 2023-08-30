/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:43:21 by adardour          #+#    #+#             */
/*   Updated: 2023/08/29 12:27:50 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	check_(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0' || map[i][j] == 'N' \
			|| map[i][j] == 'S' \
			|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (map[i][j + 1] == '.' || \
				map[i][j - 1] == '.' || \
				map[i + 1][j] == '.' || \
				map[i - 1][j] == '.')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*complete_line(char *line, int longest_length)
{
	char	*return_line;
	int		rest;
	int		i;

	rest = longest_length - strlen(line);
	if (check_line(line))
		rest += 1;
	return_line = malloc((sizeof(char) * longest_length) + 1);
	if (!return_line)
		return (NULL);
	i = -1;
	while (++i < longest_length && line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '\n')
		{
			if (line[i] == ' ')
				return_line[i] = '.';
			else
				return_line[i] = line[i];
		}
	}
	while (rest--)
		return_line[i++] = '.';
	return_line[i] = '\0';
	return (return_line);
}

void	complete_the_map(int longest_length, t_data *data)
{
	int	i;

	i = 0;
	while (data->map_represent[i] != NULL)
	{
		free(data->map_represent[i]);
		data->map_represent[i] = complete_line(data->map_represent[i], \
		longest_length);
		if (data->map_represent[i] == NULL)
		{
			perror("");
			exit(1);
		}
		i++;
	}
}

int	get_longest_length(char **represent_map)
{
	int	index;
	int	length;

	index = 0;
	length = ft_strlen(represent_map[0]);
	if (check_line(represent_map[0]))
		length -= 1;
	while (represent_map[index])
	{
		if (ft_strlen(represent_map[index]) > length)
		{
			length = ft_strlen(represent_map[index]);
			if (check_line(represent_map[index]))
				length -= 1;
		}
		index++;
	}
	return (length);
}
