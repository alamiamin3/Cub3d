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

int	check_indentifier(char *identifier)
{
	return (!ft_strcmp(identifier, "NO") || !ft_strcmp(identifier, "SO") || 
	!ft_strcmp(identifier, "WE") || !ft_strcmp(identifier, "EA"));
}

int	put(char *line, t_data *data)
{
	static int	flags;
	char		**spliting;

	spliting = ft_split(line, ' ');
	if (!ft_strcmp(spliting[0], "SO"))
	{
		if (data->texture.so)
			free(data->texture.so);
		data->texture.so = ft_substr(spliting[1],0 , ft_strlen(spliting[1]) - 1);
	}
	else if (!ft_strcmp(spliting[0], "NO"))
	{
		if (data->texture.no)
			free(data->texture.no);
		data->texture.no = ft_substr(spliting[1],0 , ft_strlen(spliting[1]) - 1);
	}
	else if (!ft_strcmp(spliting[0], "WE"))
	{
		if (data->texture.we)
			free(data->texture.we);
		data->texture.we = ft_substr(spliting[1],0 , ft_strlen(spliting[1]) - 1);
	}
	else if (!ft_strcmp(spliting[0], "EA"))
	{
		if (data->texture.ea)
			free(data->texture.ea);
		data->texture.ea = ft_substr(spliting[1],0 , ft_strlen(spliting[1]) - 1);
	}
	free_things(spliting);
	return (1);
}
