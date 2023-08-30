/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:03:03 by adardour          #+#    #+#             */
/*   Updated: 2023/08/24 13:40:39 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	**allocate(char **spliting, int count)
{
	spliting = malloc((sizeof(char *) * count) + 1);
	if (!spliting)
		exit(1);
	return (spliting);
}

int	get_length(char *line, int del)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != del)
		i++;
	return (i);
}

int	get_count(char *line, int del)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (line[i] != '\0')
	{
		if (line[i] != del && line[i] != '\0')
		{
			size++;
			while (line[i] != del && line[i] != '\0')
				i++;
		}
		while (line[i] == del && line[i] != '\0')
			i++;
	}
	return (size);
}

char	**ft_split(char *line, int del)
{
	char	**spliting;
	int		i;
	int		j;
	int		count;

	count = get_count(line, del);
	spliting = allocate(spliting, count);
	i = -1;
	while (++i < count)
	{
		while (*line != '\0' && *line == del)
			line++;
		if (*line != '\0' && *line != del)
		{
			j = 0;
			spliting[i] = malloc((sizeof(char) * get_length(line, del)) + 1);
			while (*line != '\0' && *line != del)
				spliting[i][j++] = *line++;
			spliting[i][j] = '\0';
			while (*line != '\0' && *line == del)
				line++;
		}
	}
	spliting[i] = NULL;
	return (spliting);
}
