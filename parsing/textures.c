/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:11:44 by adardour          #+#    #+#             */
/*   Updated: 2023/09/01 17:57:03 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include "../include/parsing.h"

void	free_(t_mlx *mlx)
{
	printf("error \n");
	free_data(mlx->data);
	free_things(mlx->data->map_represent);
}

void	handle_textures(t_mlx *mlx)
{
	mlx->text_n.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, \
	mlx->data->texture.no, &mlx->text_n.w, &mlx->text_n.h);
	if (!mlx->text_n.img.img_ptr)
		return (free_(mlx), exit(1));
	mlx->text_n.img.data = mlx_get_data_addr(mlx->text_n.img.img_ptr, \
	&mlx->text_n.img.bpp, &mlx->text_n.img.size, &mlx->text_n.img.endian);
	mlx->text_s.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, \
	mlx->data->texture.so, &mlx->text_s.w, &mlx->text_s.h);
	if (!mlx->text_s.img.img_ptr)
		return (free_(mlx), exit(1));
	mlx->text_s.img.data = mlx_get_data_addr(mlx->text_s.img.img_ptr, \
	&mlx->text_s.img.bpp, &mlx->text_s.img.size, &mlx->text_s.img.endian);
	mlx->text_e.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, \
	mlx->data->texture.ea, &mlx->text_e.w, &mlx->text_e.h);
	if (!mlx->text_e.img.img_ptr)
		return (free_(mlx), exit(1));
	mlx->text_e.img.data = mlx_get_data_addr(mlx->text_e.img.img_ptr, \
	&mlx->text_e.img.bpp, &mlx->text_e.img.size, &mlx->text_e.img.endian);
	mlx->text_w.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, \
	mlx->data->texture.we, &mlx->text_w.w, &mlx->text_w.h);
	if (!mlx->text_w.img.img_ptr)
		return (free_(mlx), exit(1));
	mlx->text_w.img.data = mlx_get_data_addr(mlx->text_w.img.img_ptr, \
	&mlx->text_w.img.bpp, &mlx->text_w.img.size, &mlx->text_w.img.endian);
}
