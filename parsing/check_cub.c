/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:35:58 by adardour          #+#    #+#             */
/*   Updated: 2023/09/01 18:38:23 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include "../include/parsing.h"

int	check_cub(char *path)
{
	char	*extension;

	extension = ft_strrchr(path, '.') + 1;
	if (ft_strcmp(extension, "cub"))
	{
		printf("the extension must be .cub");
		exit(1);
	}
	return (1);
}
