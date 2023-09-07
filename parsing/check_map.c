/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:09:48 by adardour          #+#    #+#             */
/*   Updated: 2023/09/07 16:33:25 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	check_symbols(char	**represent_map)
{
	int	i;
	int	w;
	int	e;
	int	o;

	w = 0;
	e = 0;
	o = 0;
	i = 0;
	while (represent_map[i])
	{
		if (!check_characters(represent_map[i], &w, &e, &o))
			return (0);
		i++;
	}
	if (o > 1 || o == 0)
	{
		printf("orientation should contain ones\n");
		exit(1);
	}
	return (1);
}

int	get_index(char *line, int from)
{
	int	i;
	int	length;

	length = 0;
	if (from == 0)
	{
		i = 0;
		while (line[i] != '\0' && line[i] == '.')
			i++;
	}
	else
	{
		length = ft_strlen(line) - 1;
		while (line[length] != '\0' && line[length] == '.')
			length--;
	}
	return (length);
}

int	check_line_(char *line)
{
	int	i;

	i = 0;
	while ((size_t)i < ft_strlen(line))
	{
		if (line[i] != '.')
			return (1);
		i++;
	}
	return (0);
}

int	check_map(char **represent_map)
{
	int	i;
	int	j;

	j = -1;
	while (represent_map[0][++j])
	{
		if (represent_map[0][j] != '.' && represent_map[0][j] != '1')
			return (0);
	}
	i = 0;
	while (represent_map[++i])
	{
		if ((represent_map[i][get_index(represent_map[i], 0)] != '.' \
		&& represent_map[i][get_index(represent_map[i], 1)] != '.'))
		{
			if ((represent_map[i][get_index(represent_map[i], 0)] != '1' \
			|| represent_map[i][get_index(represent_map[i], 1)] != '1'))
				return (0);
		}
	}
	check_last_line(represent_map, i - 1);
	return (1);
}
