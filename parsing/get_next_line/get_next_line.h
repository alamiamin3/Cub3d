/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:36:38 by adardour          #+#    #+#             */
/*   Updated: 2022/11/28 18:26:22 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int			check_if_there_newline(char *line);
char		*concatenation(char *s1, char *s2);
char		*get_next_line(int fd);
size_t		ft_strlen(char *s);

typedef struct t_get_next_line
{
	char	*ptr;
	size_t	i;
	size_t	j;
	ssize_t	bytes;
	char	*buffer;
	char	*line;
	int		out;
}			t_get_next_line;

#endif