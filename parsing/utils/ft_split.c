/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:03:03 by adardour          #+#    #+#             */
/*   Updated: 2023/09/01 18:18:42 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	**allocate(char **spliting, int count)
{
	spliting = NULL;
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
	t_help	help;

	help.count = get_count(line, del);
	help.spliting = allocate(help.spliting, help.count);
	help.i = -1;
	while (++help.i < help.count)
	{
		while (*line != '\0' && *line == del)
			line++;
		if (*line != '\0' && *line != del)
		{
			help.j = 0;
			help.spliting[help.i] = malloc((sizeof(char) * \
			get_length(line, del)) + 1);
			while (*line != '\0' && *line != del)
				help.spliting[help.i][help.j++] = *line++;
			help.spliting[help.i][help.j] = '\0';
			while (*line != '\0' && *line == del)
				line++;
		}
	}
	help.spliting[help.i] = NULL;
	return (help.spliting);
}
