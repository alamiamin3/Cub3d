/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:49:09 by aalami            #+#    #+#             */
/*   Updated: 2023/08/17 17:17:30 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img.data + (y * mlx->img.size + x * (mlx->img.bpp / 8));
	*(unsigned int*)dst = color;
}
void	draw_line(t_mlx *mlx, float angle, float x1, float y1)
{
	float dx;
	float dy;
	float x2;
	float y2;
	
	int step;
	float x_inc;
	float y_inc;
	int i;

	i = 0;
	x2 = x1 + cos(angle) * 20 ;
	y2 = y1 + sin(angle) * 20;
	dx = x2 - (mlx->player.x * MAP_SCALE);
	dy = y2 - (mlx->player.y * MAP_SCALE);
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	while (i < step)
	{
		my_mlx_pixel_put(mlx,x1, y1, 0xF93308);
		x1 += x_inc;
		y1 += y_inc;
		i++;
	}
}

int	render_map(t_mlx *mlx)
{
	// mlx_clear_window(mlx->mlx_init, mlx->mlx_win);
		if (mlx->player.turn_direction != 0)
		rotate_player(mlx);
    // while (mlx->player.rotat_angle >= 2 * PI ) {
    //     mlx->player.rotat_angle-= 2 * M_PI; 
    // }
		
	// }
	if (mlx->player.walk_direction != 0)
	{
		if (check_wall(mlx))
			walk_player(mlx);
	}
	cast_rays(mlx);
	render_projection(mlx);
	render_walls(mlx);
	render_ceiling(mlx);
	render_floor(mlx);
	draw_map_img(mlx->map, mlx);
	draw_player(mlx);
	draw_rays(mlx);
	mlx_put_image_to_window(mlx->mlx_init, mlx->mlx_win, mlx->img.img_ptr, 0, 0);
	return (0);
}

char** allocate_map(char map[14][13], int rows, int cols) {
    char** arr = (char**)malloc(rows * sizeof(char*));


    for (int i = 0; i < rows; i++) {
        arr[i] = (char*)malloc(cols * sizeof(char));

        for (int j = 0; j < cols; j++) {
            arr[i][j] = map[i][j];
        }
    }

    return arr;
}
int	check_wall(t_mlx *mlx)
{
	int	pos_x;
	int	pos_y;
	if (mlx->player.walk_direction != 0)
	{
		pos_x = (mlx->player.x + ((cos(mlx->player.rotat_angle) * mlx->player.mov_speed) * mlx->player.walk_direction)) / TILE_SIZE;
		pos_y = (mlx->player.y + ((sin(mlx->player.rotat_angle) * mlx->player.mov_speed) * mlx->player.walk_direction)) / TILE_SIZE;
		if (mlx->map[pos_y][pos_x] == '1')
			return (0);
	}
	return (1);
}

int	release(int key, t_mlx *mlx)
{
	if (key == 13 || key == 1)	
		mlx->player.walk_direction = 0;
	if (key == 123 || key == 124)
		mlx->player.turn_direction = 0;
	return (0);	
}

void	fill_text_arr(t_mlx *mlx)
{
	int color;
	int	i = 0;
	int x;
	int y;
	char *dst;
	x = 0;
	y = 0;

	while (y < mlx->texture.h * mlx->texture.img.size)
	{
		x = 0;
		while(x < mlx->texture.w)
		{
			dst = mlx->texture.img.data + (y  + x * ( mlx->texture.img.bpp / 8));
			mlx->text_arr[i] = *(unsigned int*)dst;
			i++;
			x ++;
		}
		y += mlx->texture.img.size;
	}
}
void	fill_textv_arr(t_mlx *mlx)
{
	int color;
	int	i = 0;
	int x;
	int y;
	char *dst;
	x = 0;
	y = 0;

	while (y < mlx->texture_v.h * mlx->texture_v.img.size)
	{
		x = 0;
		while(x < mlx->texture_v.w)
		{
			dst = mlx->texture_v.img.data + (y  + x * ( mlx->texture_v.img.bpp / 8));
			mlx->text_v_arr[i] = *(unsigned int*)dst;
			i++;
			x ++;
		}
		y += mlx->texture_v.img.size;
	}
}
int mouse_move(int key, t_mlx *mlx)
{
	printf("%d", key);
	return (0);
}
int	main()
{
	char map[14][31] = {
								{' ', ' ' , ' ' , ' ' , '1', '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1', '1' , '1' , '1' , '1', '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1', '1'} ,
								{'1', '1' , '1' , '1' , '1', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , 'N', '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1' , '0' , '0' , '0' , '0' , '0', '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '1' } ,
								{'1', '1' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '1' } ,
								{'1', '0' , '1' , '0' , '0', '0' , '1' , '0' , '1' , '1' , '1' , '1' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '1' } ,
								{'1', '1' , '0' , '0' , '0', '0' , '1' , '0' , '1' , ' ' , ' ' , '1' , '1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '1' , ' ' , ' ' , '1' , '0', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '1' } ,
								{'1', '1' , '1' , '1' , '1', '1' , '1' , '1' , '1' , ' ' , ' ' , '1' , '1', '1' , '1' , '1' , '1', '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1', '1' }
							};
	t_mlx	*mlx;
	static int f;
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	   mlx->map = (char**)malloc(14 * sizeof(char*));


    for (int i = 0; i < 14; i++) {
       mlx->map[i] = (char*)malloc(30 * sizeof(char));

        for (int j = 0; j < 31; j++) {
            mlx->map[i][j] = map[i][j];
        }
    }
	
	// mlx->map = allocate_map(map, 14, 13);
	mlx->rays = (t_ray *)malloc(sizeof(t_ray) * mlx->win_w);
	init_player(mlx);
	mlx->win_h = 14 * TILE_SIZE;
	mlx->win_w = 31 * TILE_SIZE;
	mlx->mlx_init = mlx_init();
	if (f == 0)
	{
		mlx->mlx_win = mlx_new_window(mlx->mlx_init, mlx->win_w, mlx->win_h, "cub3d");
		mlx->img.img_ptr = mlx_new_image(mlx->mlx_init, mlx->win_w, mlx->win_h);
		mlx->img.data = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size, &mlx->img.endian);
		init_rays_dir(mlx);
		mlx->texture.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, "./textures/greystone.xpm", &mlx->texture.w, &mlx->texture.h);
		mlx->texture.img.data = mlx_get_data_addr(mlx->texture.img.img_ptr, &mlx->texture.img.bpp, &mlx->texture.img.size, &mlx->texture.img.endian);
		mlx->texture_v.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, "./textures/bluestone.xpm", &mlx->texture_v.w, &mlx->texture_v.h);
		mlx->texture_v.img.data = mlx_get_data_addr(mlx->texture_v.img.img_ptr, &mlx->texture_v.img.bpp, &mlx->texture_v.img.size, &mlx->texture_v.img.endian);
		mlx->text_arr = (int *)malloc(sizeof(int) * mlx->texture.w * mlx->texture.h);
		mlx->text_v_arr = (int *)malloc(sizeof(int) * mlx->texture_v.w * mlx->texture_v.h);
		fill_text_arr(mlx);
		fill_textv_arr(mlx);
		
	}
	
	mlx_hook(mlx->mlx_win, 06, 1L<<6, mouse_move, mlx);
	mlx_hook(mlx->mlx_win, 03, 0, release, mlx);
	mlx_hook(mlx->mlx_win, 02, 1L<<2, move_player, mlx);
	mlx_loop_hook(mlx->mlx_init, render_map, mlx);
	mlx_loop(mlx->mlx_init);
	
}