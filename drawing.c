/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:42:05 by adardour          #+#    #+#             */
/*   Updated: 2023/09/05 20:42:42 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub.h"
#include "./include/parsing.h"

int	release(int key, t_mlx *mlx)
{
	if (key == KEY_UP || key == KEY_DOWN)
		mlx->player.walk_ud = 0;
	if (key == KEY_RIGHT || key == KEY_LEFT)
		mlx->player.walk_rl = 0;
	if (key == ARR_LEFT || key == ARR_RIGHT)
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
		if (mlx->player.walk_ud != 0 || mlx->player.walk_rl != 0)
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

void	drawing(t_data *data)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (perror(""), exit(1));
	mlx->data = data;
	mlx->mlx_init = data->init;
	mlx->map = data->map_represent;
	init_player(mlx);
	mlx->win_h = 830;
	mlx->win_w = 1850;
	printf("%d %d\n", mlx->win_h, mlx->win_w);
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
