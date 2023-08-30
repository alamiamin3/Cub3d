/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:36:31 by adardour          #+#    #+#             */
/*   Updated: 2022/11/28 20:51:03 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_if_there_newline(char *line)
{
	while (*line != '\0')
	{
		if (*line == 10)
			return (1);
		line++;
	}
	return (-1);
}

char	*concatenation(char *s1, char *s2)
{
	t_get_next_line	t_get_next;

	t_get_next = (t_get_next_line){.ptr = NULL, .i = 0, .j = 0};
	if (s1 == NULL)
		s1 = "";
	t_get_next.ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (t_get_next.ptr == NULL)
		return (NULL);
	while (s1[t_get_next.i] != '\0')
	{
		t_get_next.ptr[t_get_next.i] = s1[t_get_next.i];
		t_get_next.i++;
	}
	while (s2[t_get_next.j] != '\0')
	{
		t_get_next.ptr[t_get_next.i] = s2[t_get_next.j];
		t_get_next.i++;
		t_get_next.j++;
	}
	t_get_next.ptr[t_get_next.i] = '\0';
	return (t_get_next.ptr);
}

size_t	ft_strlen(char *s)
{
	size_t	size;

	size = 0;
	if (s == NULL)
		return (0);
	while (s[size] != '\0')
	{
		size++;
	}
	return (size);
}
