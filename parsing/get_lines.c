/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:20:19 by adardour          #+#    #+#             */
/*   Updated: 2023/08/24 13:40:38 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/parsing.h"

char	*get_begin(int reached_map, int fd)
{
	char	*line;
	char	*close_file;

	line = get_next_line(fd);
	while (--reached_map > 0 && line)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && !ft_strcmp(line, "\n"))
	{
		free(line);
		line = get_next_line(fd);
	}
	close_file = get_next_line(fd);
	while (close_file)
	{
		free(close_file);
		close_file = get_next_line(fd);
	}
	close(fd);
	return (line);
}
