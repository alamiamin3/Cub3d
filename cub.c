/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:49:09 by aalami            #+#    #+#             */
/*   Updated: 2023/08/13 22:41:26 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	x2 = x1 + cos(angle) * 110;
	y2 = y1 + sin(angle) * 110;
	dx = x2 - mlx->player.x;
	dy = y2 - mlx->player.y;
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
void	draw_ray_line(t_mlx *mlx, float angle, float x1, float y1, int j)
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
	x2 = x1 + cos(angle) * mlx->rays[j].dis;
	y2 = y1 + sin(angle) * mlx->rays[j].dis;
	dx = x2 - mlx->player.x;
	dy = y2 - mlx->player.y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	while (i < step)
	{
		my_mlx_pixel_put(mlx,MAP_SCALE * x1, MAP_SCALE * y1, 0x00FF42);
		x1 += x_inc;
		y1 += y_inc;
		i++;
	}
}

void	draw_map_img(char **map,  t_mlx *mlx)
{
	int	i;
	int	j;
	float x;
	float y;
	static int first;
	i = 0;
	j = 0;
	
	while (i < mlx->win_h)
	{
		j = 0;
		while (j < mlx->win_w)
		{
			y = 0;
			if (map[i/TILE_SIZE][j/TILE_SIZE] == '1')
			{
				while (y < TILE_SIZE)
				{
					x = 0;
					while (x < TILE_SIZE)
					{
						my_mlx_pixel_put(mlx, MAP_SCALE * (x + j), MAP_SCALE * (y + i), 0x000000);	
						x++;
					}
					y++;
				}
			}
			else
			{
				while (y < TILE_SIZE)
				{
					x = 0;
					while (x < TILE_SIZE)
					{
						my_mlx_pixel_put(mlx, MAP_SCALE * (x + j), MAP_SCALE * (y + i), 0xFFFFFF);	
						x++;
					}
					y++;
				}
				
			}
			j += TILE_SIZE;
		}
		i += TILE_SIZE;
	}
	
}

int	draw_player(t_mlx *mlx)
{
	float x;
	float y;
	y = 0;
		my_mlx_pixel_put(mlx, MAP_SCALE * mlx->player.x , MAP_SCALE * (mlx->player.y), 0xF93308);			
	return (0);
}

void	normalize_ray(t_mlx *mlx, int i, float ray_angle)
{

	while (ray_angle < 0 )
        ray_angle += 2 * PI;
    while (ray_angle >= 2 * PI )
        ray_angle -= 2 * PI; 
	mlx->rays[i].ray_angle  = ray_angle;
}

void	define_direction(t_mlx *mlx, int i)
{
	// mlx->rays[i].f_d = mlx->rays[i].ray_angle > 0 && mlx->rays[i].ray_angle < PI ? 1 : 0;
	// mlx->rays[i].f_u = !mlx->rays[i].f_d;
	// mlx->rays[i].f_r = mlx->rays[i].ray_angle > 1.5 * PI || mlx->rays[i].ray_angle < PI / 2 ? 1 : 0;
	// mlx->rays[i].f_l = !mlx->rays[i].f_r;
	if (mlx->rays[i].ray_angle > 0 && mlx->rays[i].ray_angle < PI)
		mlx->rays[i].f_d = 1;
	else
		mlx->rays[i].f_d = 0;
	if (mlx->rays[i].ray_angle > 1.5 * PI || mlx->rays[i].ray_angle < PI / 2)
		mlx->rays[i].f_r = 1;
	else
		mlx->rays[i].f_r = 0;
	mlx->rays[i].f_l = !mlx->rays[i].f_r;
	mlx->rays[i].f_u = !mlx->rays[i].f_d;
	
}
void	cast_rays(t_mlx *mlx)
{
	int	i;
	float ray_angle;

	i = 0;
	ray_angle = mlx->player.rotat_angle - (FOV / 2);
	static int s;
	while (i < mlx->win_w)
	{
		// mlx->rays[i].ray_angle  = ray_angle;
		normalize_ray(mlx, i, ray_angle);
		define_direction(mlx, i);
		get_intersect_and_draw(mlx, i);
		ray_angle += FOV / (mlx->win_w);
		i++;
	}
}
void	draw_rays(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < mlx->win_w)
	{
		draw_ray_line(mlx, mlx->rays[i].ray_angle, mlx->player.x, mlx->player.y, i);
		i++;
	}
}
int	render_map(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_init, mlx->mlx_win);
	cast_rays(mlx);
	render_projection(mlx);
	render_ceiling(mlx);
	render_floor(mlx);
	render_walls(mlx);
	draw_map_img(mlx->map, mlx);
	draw_player(mlx);
	draw_rays(mlx);
	// get_horizontal_intersect(mlx);
	mlx_put_image_to_window(mlx->mlx_init, mlx->mlx_win, mlx->img.img_ptr, 0, 0);
	// mlx_destroy_image(mlx->mlx_init, mlx->img.img_ptr);
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
int	check_wall(t_mlx *mlx, int move)
{
	int	pos_x;
	int	pos_y;
	if (move == 13)
	{
		pos_x = (mlx->player.x + (cos(mlx->player.rotat_angle) * mlx->player.mov_speed ))/ TILE_SIZE;
		pos_y = (mlx->player.y + (sin(mlx->player.rotat_angle) * mlx->player.mov_speed)) / TILE_SIZE ;
	}
	else if (move == 1)
	{
		pos_x = (mlx->player.x - (cos(mlx->player.rotat_angle) * mlx->player.mov_speed ))/ TILE_SIZE;
		pos_y = (mlx->player.y - (sin(mlx->player.rotat_angle) * mlx->player.mov_speed)) / TILE_SIZE ;
	}
	else if (move == 2)
	{
		pos_x = (mlx->player.x + mlx->player.mov_speed) / TILE_SIZE;
		pos_y = mlx->player.y / TILE_SIZE;
	// printf("map[%d][%d] , %c \n", pos_y, pos_x, mlx->map[pos_y][pos_x]);
	}
	else
	{
		pos_x = (mlx->player.x - mlx->player.mov_speed) / TILE_SIZE;
		pos_y = mlx->player.y / TILE_SIZE;
	}
	if (mlx->map[pos_y][pos_x] == '1')
	{
		return (0);
	}
	return (1);
}
void	move_up(t_mlx *mlx)
{
	mlx->player.x += cos(mlx->player.rotat_angle) * mlx->player.mov_speed;
	mlx->player.y += sin(mlx->player.rotat_angle) * mlx->player.mov_speed;
}
void	move_down(t_mlx *mlx)
{
	mlx->player.x -= cos(mlx->player.rotat_angle) * mlx->player.mov_speed;
	mlx->player.y -= sin(mlx->player.rotat_angle) * mlx->player.mov_speed;
}
void	move_right(t_mlx *mlx)
{
	mlx->player.x += mlx->player.mov_speed;
}
void	move_left(t_mlx *mlx)
{
	mlx->player.x -= mlx->player.mov_speed;
}
int	move_player(int key, t_mlx *mlx)
{
	if (key == 123)
	{
		mlx->player.rotat_angle -= mlx->player.rot_speed;
		while (mlx->player.rotat_angle < 0 ) {
        mlx->player.rotat_angle += 2 * PI; 
    }
    while (mlx->player.rotat_angle >= 2 * PI ) {
        mlx->player.rotat_angle-= 2 * M_PI; // Subtract 2π to bring it within range
    }
	}
	if (key == 124)
	{
		mlx->player.rotat_angle += mlx->player.rot_speed;
		while (mlx->player.rotat_angle < 0 ) {
        mlx->player.rotat_angle += 2 * PI; 
    }

    while (mlx->player.rotat_angle >= 2 * PI ) {
        mlx->player.rotat_angle-= 2 * M_PI; 
    }
		
	}
	if (!check_wall(mlx, key))
		return (1);
	if (key == 13)
		move_up(mlx);
	if (key == 1)
		move_down(mlx);
	// if (key == 0)
	// 	move_left(mlx);
	// if (key == 2)
	// 	move_right(mlx);
	return (0);
}
void	get_player_pos(t_mlx *mlx)
{
	int	i;
	int j;
	printf("ddd\n");
	i = 0;
	while(i <14)
	{
		j = 0;
		while (j < 13)
		{
			if (mlx->map[i][j] == 'N')
			{
				mlx->player.x = j * TILE_SIZE + TILE_SIZE / 2;
				mlx->player.y = i * TILE_SIZE + TILE_SIZE / 2;
				return ;
			}
			j++;
		}
		i++;
	}
}
void	init_player(t_mlx *mlx)
{
		get_player_pos(mlx);
		
	// draw_map_img(mlx->map, mlx);
	mlx->player.rotat_angle = -90 * (PI / 180);
	mlx->player.rot_speed = 3 * (PI / 180);
	mlx->player.mov_speed = 3;
}
void	init_rays_dir(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < mlx->win_w)
	{
		mlx->rays[i].f_d = 0;
		mlx->rays[i].f_u = 0;
		mlx->rays[i].f_r = 0;
		mlx->rays[i].f_l = 0;
		i++;
	}
	
}

int	main()
{
	char map[14][25] = {
								{'1', '1' , '1' , '1' , '1', '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1', '1' , '1' , '1' , '1', '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '1' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '1' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '1' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , 'N' , '0', '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0', '0' , '0' , '0' , '0', '0' , '1' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '1' , '1' , '1' , '1', '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1', '1' , '1' , '1' , '1', '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' }
							};
	t_mlx	*mlx;
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	   mlx->map = (char**)malloc(14 * sizeof(char*));


    for (int i = 0; i < 14; i++) {
       mlx->map[i] = (char*)malloc(25 * sizeof(char));

        for (int j = 0; j < 25; j++) {
            mlx->map[i][j] = map[i][j];
        }
    }
	
	// mlx->map = allocate_map(map, 14, 13);
	init_player(mlx);
	mlx->win_h = 14 * TILE_SIZE;
	mlx->win_w = 25 * TILE_SIZE;
	mlx->mlx_init = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx_init, mlx->win_w, mlx->win_h, "cub3d");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_init, mlx->win_w, mlx->win_h);
	mlx->img.data = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size, &mlx->img.endian);
	mlx->rays = (t_ray *)malloc(sizeof(t_ray) * mlx->win_w);
	init_rays_dir(mlx);
	mlx_hook(mlx->mlx_win, 02, 0, move_player, mlx);
	mlx_loop_hook(mlx->mlx_init, render_map, mlx);
	mlx->texture.img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_init, "./textures/walll.xpm", &mlx->texture.w, &mlx->texture.h);
	mlx->texture.img.data = mlx_get_data_addr(mlx->texture.img.img_ptr, &mlx->texture.img.bpp, &mlx->texture.img.size, &mlx->texture.img.endian);
	mlx_loop(mlx->mlx_init);
	
}