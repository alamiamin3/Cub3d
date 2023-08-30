/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:30:46 by adardour          #+#    #+#             */
/*   Updated: 2023/08/30 12:37:49 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	check_digits(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (color[i] < 40 || color[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int	check_range(t_ceiling ceiling, t_floor floor)
{
	if ((atoi(ceiling.r) > 255 || atoi(ceiling.r) < 0) || \
	(atoi(ceiling.g) > 255 || atoi(ceiling.g) < 0) || \
	atoi(ceiling.b) > 255 || atoi(ceiling.b) < 0)
		return (0);
	else if ((atoi(floor.r) > 255 || atoi(floor.r) < 0) || \
	(atoi(floor.g) > 255 || atoi(floor.g) < 0) || \
	atoi(floor.b) > 255 || atoi(floor.b) < 0)
		return (0);
	return (1);
}

void	colors(t_data *data)
{
	if (!check_range(data->ceiling, data->floor))
	{
		printf("Range of RGB must be (0-255)");
		exit(1);
	}
	data->ceiling.color = get_color(data->ceiling.r, \
	data->ceiling.g, data->ceiling.b);
	data->floor.color = get_color(data->floor.r, data->floor.g, data->floor.b);
}

int	check_rgbs(t_ceiling ceiling, t_floor floor)
{
	if (!floor.r || !floor.g || !floor.b \
	|| !ceiling.r || !ceiling.g \
	|| !ceiling.b)
		return (0);
	if (check_car(ceiling.r, ceiling.g, ceiling.b) != 3 \
	|| check_car(floor.r, floor.g, floor.b) != 3)
		return (0);
	return (1);
}

int	check_color(char *color)
{
	char	*trim;
	int		i;

	i = 0;
	trim = ft_strtrim(color, " \n");
	if (!check_digits(trim))
	{
		free(trim);
		return (0);
	}
	free(trim);
	return (1);
}
