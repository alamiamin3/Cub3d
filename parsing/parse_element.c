/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:29:39 by adardour          #+#    #+#             */
/*   Updated: 2023/08/24 15:02:05 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	parse_element(t_data *data)
{
	if (!data->texture.ea \
	|| !data->texture.so \
	|| !data->texture.we \
	|| !data->texture.no \
	|| !data->floor.r \
	|| !data->floor.g \
	|| !data->floor.b \
	|| !data->ceiling.r \
	|| !data->ceiling.g \
	|| !data->ceiling.b)
	{
		printf("error\n");
		return (0);
	}
	return (1);
}
