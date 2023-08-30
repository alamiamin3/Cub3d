/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:45:07 by adardour          #+#    #+#             */
/*   Updated: 2023/08/29 20:19:30 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	open_file(char *filename)
{
	return (open(filename, O_RDONLY));
}

void	open_texture(char *n, char *s, char *w, char *e)
{
	int	fd_n;
	int	fd_s;
	int	fd_w;
	int	fd_e;

	fd_e = open_file(e);
	fd_n = open_file(n);
	fd_s = open_file(s);
	fd_w = open_file(w);
	if (fd_n == -1 || fd_s == -1 || fd_w == -1 || fd_e == -1)
		return (perror("Texture Error : "), exit(1));
}
