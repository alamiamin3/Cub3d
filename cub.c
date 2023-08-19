/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:49:09 by aalami            #+#    #+#             */
/*   Updated: 2023/08/19 16:58:01 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img.data + (y * mlx->img.size + x * (mlx->img.bpp / 8));
	*(unsigned int*)dst = color;
}
// void	draw_line(t_mlx *mlx, float angle, float x1, float y1)
// {
// 	float dx;
// 	float dy;
// 	float x2;
// 	float y2;
	
// 	int step;
// 	float x_inc;
// 	float y_inc;
// 	int i;

// 	i = 0;
// 	x2 = x1 + cos(angle) * 20 ;
// 	y2 = y1 + sin(angle) * 20;
// 	dx = x2 - (mlx->player.x * MAP_SCALE);
// 	dy = y2 - (mlx->player.y * MAP_SCALE);
// 	if (fabs(dx) > fabs(dy))
// 		step = fabs(dx);
// 	else
// 		step = fabs(dy);
// 	x_inc = dx / step;
// 	y_inc = dy / step;
// 	while (i < step)
// 	{
// 		my_mlx_pixel_put(mlx,x1, y1, 0xF93308);
// 		x1 += x_inc;
// 		y1 += y_inc;
// 		i++;
// 	}
// }

int	render_map(t_mlx *mlx)
{
	if (mlx->player.turn_direction != 0)
		rotate_player(mlx);
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
		pos_x = (mlx->player.x + ((cos(mlx->player.rotat_angle) * mlx->player.mov_speed * 5) * mlx->player.walk_direction)) / TILE_SIZE;
		pos_y = (mlx->player.y+ ((sin(mlx->player.rotat_angle) * mlx->player.mov_speed * 5) * mlx->player.walk_direction)) / TILE_SIZE;
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

void	fill_text_arr(t_mlx *mlx, t_texture *text, int *text_arr)
{
	int color;
	int	i = 0;
	int x;
	int y;
	char *dst;
	x = 0;
	y = 0;
	while (y < text->h * text->img.size)
	{
		x = 0;
		while(x < text->w)
		{
			dst = text->img.data + (y  + x * ( text->img.bpp / 8));
			text_arr[i] = *(unsigned int*)dst;
			i++;
			x ++;
		}
		y += text->img.size;
	}
}
// void	fill_textv_arr(t_mlx *mlx)
// {
// 	int color;
// 	int	i = 0;
// 	int x;
// 	int y;
// 	char *dst;
// 	x = 0;
// 	y = 0;

// 	while (y < mlx->texture_v.h * mlx->texture_v.img.size)
// 	{
// 		x = 0;
// 		while(x < mlx->texture_v.w)
// 		{
// 			dst = mlx->texture_v.img.data + (y  + x * ( mlx->texture_v.img.bpp / 8));
// 			mlx->text_v_arr[i] = *(unsigned int*)dst;
// 			i++;
// 			x ++;
// 		}
// 		y += mlx->texture_v.img.size;
// 	}
// }
int mouse_move(int x, int y, t_mlx *mlx)
{
	static int x_s;
	static int y_s;
	static int i;

	if (x_s == x && y_s == y)
		return (0);
	else 
	{
		x_s = x;
		y_s = y;
		if ((int)mlx->player.x < x_s )
			mlx->player.rotat_angle -= 1 * (PI / 180);
		else if ((int)mlx->player.x > x_s)
			mlx->player.rotat_angle += 1 * (PI / 180);
		while (mlx->player.rotat_angle < 0)
			mlx->player.rotat_angle += 2 * PI;
		while (mlx->player.rotat_angle >= 2 * PI)
			mlx->player.rotat_angle -= 2 * M_PI;
	}
	printf("x = %d y = %d    PLAYER_X = %f   PLAYER_Y = %f\n", x, y, mlx->player.x, mlx->player.y);

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
		//N
		mlx->text_n.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, "./textures/greystone.xpm", &mlx->text_n.w, &mlx->text_n.h);
		mlx->text_n.img.data = mlx_get_data_addr(mlx->text_n.img.img_ptr, &mlx->text_n.img.bpp, &mlx->text_n.img.size, &mlx->text_n.img.endian);
		//S
		mlx->text_s.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, "./textures/eagle.xpm", &mlx->text_s.w, &mlx->text_s.h);
		mlx->text_s.img.data = mlx_get_data_addr(mlx->text_s.img.img_ptr, &mlx->text_s.img.bpp, &mlx->text_s.img.size, &mlx->text_s.img.endian);
		//E
		mlx->text_e.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, "./textures/redbrick.xpm", &mlx->text_e.w, &mlx->text_e.h);
		mlx->text_e.img.data = mlx_get_data_addr(mlx->text_e.img.img_ptr, &mlx->text_e.img.bpp, &mlx->text_e.img.size, &mlx->text_e.img.endian);
		//W
		mlx->text_w.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, "./textures/bluestone.xpm", &mlx->text_w.w, &mlx->text_w.h);
		mlx->text_w.img.data = mlx_get_data_addr(mlx->text_w.img.img_ptr, &mlx->text_w.img.bpp, &mlx->text_w.img.size, &mlx->text_w.img.endian);
		
		//player image
		
		mlx->text_n_arr = (int *)malloc(sizeof(int) * mlx->text_n.w * mlx->text_n.h);
		mlx->text_s_arr = (int *)malloc(sizeof(int) * mlx->text_s.w * mlx->text_s.h);
		mlx->text_e_arr = (int *)malloc(sizeof(int) * mlx->text_e.w * mlx->text_e.h);
		mlx->text_w_arr = (int *)malloc(sizeof(int) * mlx->text_w.w * mlx->text_w.h);
		fill_text_arr(mlx, &mlx->text_n, mlx->text_n_arr);
		fill_text_arr(mlx, &mlx->text_s, mlx->text_s_arr);
		fill_text_arr(mlx, &mlx->text_e, mlx->text_e_arr);
		fill_text_arr(mlx, &mlx->text_w, mlx->text_w_arr);
		
	}
	
	// mlx_hook(mlx->mlx_win, 06, 0, mouse_move, mlx);
	mlx_hook(mlx->mlx_win, 03, 0, release, mlx);
	mlx_hook(mlx->mlx_win, 02, 1L<<2, move_player, mlx);
	mlx_loop_hook(mlx->mlx_init, render_map, mlx);
	mlx_loop(mlx->mlx_init);
	
}