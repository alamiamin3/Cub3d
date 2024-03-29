/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caracteres.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:01:11 by adardour          #+#    #+#             */
/*   Updated: 2023/09/07 16:32:35 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/parsing.h"

int	check_characters(char *line, int *w, int *e, int *o)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n')
		{
			if ((line[i] != '0' && line[i] != '1') \
			&& (line[i] != 'N' && line[i] != 'S' \
			&& line[i] != 'E' && line[i] != 'W'))
			{
				printf("symbol not valid\n");
				return (0);
			}
			else if (line[i] == 'N' || line[i] == 'S' \
			|| line[i] == 'E' || line[i] == 'W')
				(*o)++;
			else if (line[i] == '1')
				(*w)++;
			else if (line[i] == '0')
				(*e)++;
		}
		i++;
	}
	return (1);
}
