/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:42:05 by adardour          #+#    #+#             */
/*   Updated: 2023/08/30 17:15:57 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub.h"
#include "./include/parsing.h"

void	handle_textures(t_mlx *mlx)
{
	mlx->text_n.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, \
	"./textures/11.xpm", &mlx->text_n.w, &mlx->text_n.h);
	mlx->text_n.img.data = mlx_get_data_addr(mlx->text_n.img.img_ptr, \
	&mlx->text_n.img.bpp, &mlx->text_n.img.size, &mlx->text_n.img.endian);
	mlx->text_s.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, \
	"./textures/11.xpm", &mlx->text_s.w, &mlx->text_s.h);
	mlx->text_s.img.data = mlx_get_data_addr(mlx->text_s.img.img_ptr, \
	&mlx->text_s.img.bpp, &mlx->text_s.img.size, &mlx->text_s.img.endian);
	mlx->text_e.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, \
	"./textures/11.xpm", &mlx->text_e.w, &mlx->text_e.h);
	mlx->text_e.img.data = mlx_get_data_addr(mlx->text_e.img.img_ptr, \
	&mlx->text_e.img.bpp, &mlx->text_e.img.size, &mlx->text_e.img.endian);
	mlx->text_w.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, \
	"./textures/11.xpm", &mlx->text_w.w, &mlx->text_w.h);
	mlx->text_w.img.data = mlx_get_data_addr(mlx->text_w.img.img_ptr, \
	&mlx->text_w.img.bpp, &mlx->text_w.img.size, &mlx->text_w.img.endian);
}

int	release(int key, t_mlx *mlx)
{
	if (key == 13 || key == 1)
		mlx->player.walk_direction = 0;
	if (key == 123 || key == 124)
		mlx->player.turn_direction = 0;
	return (0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img.data + (y * mlx->img.size + x * (mlx->img.bpp / 8));
	*(unsigned int *)dst = color;
}

int	render_map(t_mlx *mlx)
{
	if (check_wall(mlx))
	{
		if (mlx->player.turn_direction != 0)
			rotate_player(mlx);
		if (mlx->player.walk_direction != 0)
			walk_player(mlx);
	}
	cast_rays(mlx);
	render_projection(mlx);
	draw_map_img(mlx->map, mlx);
	draw_player(mlx);
	draw_rays(mlx);
	mlx_put_image_to_window(mlx->mlx_init, \
	mlx->mlx_win, mlx->img.img_ptr, 0, 0);
	return (0);
}

void	drawing(t_mlx *mlx, t_data *data)
{
	mlx->data = data;
	mlx->map = data->map_represent;
	init_player(mlx);
	mlx->win_h = get_rows(data->map_represent) * TILE_SIZE;
	mlx->win_w = get_columns(data->map_represent) * TILE_SIZE;
	mlx->rays = (t_ray *)malloc(sizeof(t_ray) * mlx->win_w);
	mlx->mlx_win = mlx_new_window(mlx->mlx_init, \
	mlx->win_w, mlx->win_h, "cub3d");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_init, mlx->win_w, mlx->win_h);
	mlx->img.data = mlx_get_data_addr(mlx->img.img_ptr, \
	&mlx->img.bpp, &mlx->img.size, &mlx->img.endian);
	init_rays_dir(mlx);
	handle_textures(mlx);
	mlx_hook(mlx->mlx_win, 03, 0, release, mlx);
	mlx_hook(mlx->mlx_win, 17, 0, ft_exit, mlx);
	mlx_hook(mlx->mlx_win, 02, 0, move_player, mlx);
	mlx_loop_hook(mlx->mlx_init, render_map, mlx);
	mlx_loop(mlx->mlx_init);
}
