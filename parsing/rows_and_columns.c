/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rows_and_columns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:41:54 by adardour          #+#    #+#             */
/*   Updated: 2023/08/24 13:40:38 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	get_rows(char **represent)
{
	int	rows;

	rows = 0;
	while (represent[rows])
		rows++;
	return (rows);
}

int	get_columns(char **represent)
{
	int		column;
	int		i;
	int		j;

	i = 0;
	column = 0;
	while (represent[i])
	{
		j = 0;
		while (represent[i][j] != '\0')
		{
			column++;
			j++;
		}
		return (column);
		i++;
	}
	return (0);
}
