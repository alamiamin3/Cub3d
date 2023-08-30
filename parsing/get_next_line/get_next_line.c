/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:36:36 by adardour          #+#    #+#             */
/*   Updated: 2022/11/29 11:49:39 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_next(char *next)
{
	int		i;
	int		length_line;
	char	*str;
	int		j;

	i = 0;
	while (next[i] != '\n' && next[i] != '\0')
		i++;
	length_line = ft_strlen(next) - i;
	if (length_line == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * length_line);
	if (str == NULL)
		return (NULL);
	i++;
	j = 0;
	while (next[i] != '\0')
	{
		str[j] = next[i];
		j++;
		i++;
	}
	str[j] = '\0';
	free(next);
	return (str);
}

static char	*get_line(char *line)
{
	char	*str;
	int		j;
	int		i;

	i = 0;
	if (check_if_there_newline(line) == -1)
		return (line);
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 10)
		i++;
	str = (char *)malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = line[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_full_line(char *remember_line, int fd)
{
	t_get_next_line	t_get_next;

	t_get_next = (t_get_next_line){.bytes = 1, .out = 0};
	while (t_get_next.bytes != 0 && t_get_next.out == 0)
	{
		t_get_next.buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (t_get_next.buffer == NULL)
			return (NULL);
		t_get_next.bytes = read(fd, t_get_next.buffer, BUFFER_SIZE);
		if (t_get_next.bytes == -1 || (t_get_next.bytes == 0
				&& ft_strlen(remember_line) == 0))
		{
			free(t_get_next.buffer);
			free(remember_line);
			return (NULL);
		}
		t_get_next.buffer[t_get_next.bytes] = '\0';
		t_get_next.line = concatenation(remember_line, t_get_next.buffer);
		free(t_get_next.buffer);
		free(remember_line);
		remember_line = t_get_next.line;
		if (check_if_there_newline(remember_line) != -1)
			t_get_next.out = 1;
	}
	return (remember_line);
}

char	*get_next_line(int fd)
{
	static char	*remember_line;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	remember_line = get_full_line(remember_line, fd);
	if (ft_strlen(remember_line) == 0)
		return (NULL);
	temp = remember_line;
	line = get_line(remember_line);
	remember_line = get_next(temp);
	return (line);
}
