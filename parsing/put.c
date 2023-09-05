/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:23:19 by adardour          #+#    #+#             */
/*   Updated: 2023/09/01 16:42:23 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/cub.h"

void	north_south_west(t_data *data, char **spliting, char flag)
{
	if (flag == 'N')
	{
		if (data->texture.no)
			free(data->texture.no);
		data->texture.no = ft_substr(spliting[1], 0, \
		ft_strlen(spliting[1]) - 1);
	}
	else if (flag == 'S')
	{
		if (data->texture.so)
			free(data->texture.so);
		data->texture.so = ft_substr(spliting[1], 0, \
		ft_strlen(spliting[1]) - 1);
	}
	else if (flag == 'W')
	{
		if (data->texture.we)
			free(data->texture.we);
		data->texture.we = ft_substr(spliting[1], 0, \
		ft_strlen(spliting[1]) - 1);
	}
}

void	east(t_data *data, char **spliting)
{
	if (data->texture.ea)
		free(data->texture.ea);
	data->texture.ea = ft_substr(spliting[1], 0, \
	ft_strlen(spliting[1]) - 1);
}

int	put(char *line, t_data *data, char i)
{
	static int	flags;
	char		**spliting;

	spliting = ft_split(line, ' ');
	flags++;
	if (flags > 6)
	{
		free_things(spliting);
		return (0);
	}
	north_south_west(data, spliting, i);
	if (i == 'E')
		east(data, spliting);
	if (i == 'F' && put_rgb(data, line, 'F') == 0)
	{
		free_things(spliting);
		return (0);
	}
	if (i == 'C' && put_rgb(data, line, 'C') == 0)
	{
		free_things(spliting);
		return (0);
	}
	free_things(spliting);
	return (1);
}
