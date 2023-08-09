/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:49:09 by aalami            #+#    #+#             */
/*   Updated: 2023/08/09 22:46:57 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// void	fill_free_space_img(t_img fs)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < TILE_SIZE)
// 	{
// 		j = 0;
// 		while (j < TILE_SIZE)
// 		{
// 			if (j + 1 == TILE_SIZE || j == 0 || i + 1 == TILE_SIZE || i == 0)
// 				fs.data[i * TILE_SIZE + j] = 0xFCB5A5;
// 			else
// 				fs.data[i * TILE_SIZE + j] = 0xFFFFFF;
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	fill_wall_img(t_img wall)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < TILE_SIZE)
// 	{
// 		j = 0;
// 		while (j < TILE_SIZE)
// 		{
// 			if (j + 1 == TILE_SIZE || j == 0 || i + 1 == TILE_SIZE || i == 0)
// 				wall.data[i * TILE_SIZE + j] = 0xFCB5A5;
// 			else
// 				wall.data[i * TILE_SIZE + j] = 0x000000;
// 			j++;
// 		}
// 		i++;
// 	}
// }
// void	fill_player_img(t_img pl)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < TILE_SIZE / 6)
// 	{
// 		j = 0;
// 		while (j < TILE_SIZE / 6)
// 		{
// 			pl.data[i * (TILE_SIZE/6) + j] = 0xED2D04;
// 			j++;
// 		}
// 		i++;
// 	}
// }
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img.data + (y * mlx->img.size + x * (mlx->img.bpp / 8));
	*(unsigned int*)dst = color;
}
void	draw_line(t_mlx *mlx, double angle, double x1, double y1)
{
	double dx;
	double dy;
	double x2;
	double y2;
	
	int step;
	double x_inc;
	double y_inc;
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
void	draw_ray_line(t_mlx *mlx, double angle, double x1, double y1, int j)
{
	double dx;
	double dy;
	double x2;
	double y2;
	
	int step;
	double x_inc;
	double y_inc;
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
	while (i < step && mlx->rays[j].dis < mlx->img.size)
	{
		my_mlx_pixel_put(mlx,x1, y1, 0xF93308);
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
						if (x + 1 == TILE_SIZE || x == 0 || y + 1 == TILE_SIZE || y == 0)
							my_mlx_pixel_put(mlx, x + j, y + i, 0xFCB5A5);
							// mlx_pixel_put(mlx->mlx_init, mlx->mlx_win, x + j, y + i, 0xFCB5A5);
						else
							my_mlx_pixel_put(mlx, x + j, y + i, 0x000000);
							// mlx_pixel_put(mlx->mlx_init, mlx->mlx_win, x + j, y + i, 0x000000);
							
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
						if (x + 1 == TILE_SIZE || x == 0 || y + 1 == TILE_SIZE || y == 0)
							my_mlx_pixel_put(mlx, x + j, y + i, 0xFCB5A5);
							// mlx_pixel_put(mlx->mlx_init, mlx->mlx_win, x + j, y + i, 0xFCB5A5);
						else
							my_mlx_pixel_put(mlx, x + j, y + i, 0xFFFFFF);
							// mlx_pixel_put(mlx->mlx_init, mlx->mlx_win, x + j, y + i, 0xFFFFFF);
							
						x++;
					}
					y++;
				}
				
			}
			if (map[i/TILE_SIZE][j/TILE_SIZE] == 'N' && first == 0)
			{
				// mlx_put_image_to_window(mlx->mlx_init, mlx->mlx_win, player->img.img_ptr, j + 18  , i + 18);
				// y = 0;
				// while (y < TILE_SIZE / 8)
				// {
				// 	x = 0;
				// 	while (x < TILE_SIZE / 8)
				// 	{
				// 		// if (x + 1 == TILE_SIZE || x == 0 || y + 1 == TILE_SIZE || y == 0)
				// 		// 	mlx_pixel_put(mlx->mlx_init, mlx->mlx_win, x + j, y + i, 0xFCB5A5);
				// 		// else
				// 			mlx_pixel_put(mlx->mlx_init, mlx->mlx_win, x + j + 18 , y + i + 18, 0xF93308);
							
				// 		x++;
				// 	}
				// 	y++;
				// }
				mlx->player.x = j + 18;
				mlx->player.y = i + 18;
				first = 1;
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
	while (y < TILE_SIZE / 13.5)
	{
		x = 0;
		while (x < TILE_SIZE / 13.5)
		{
			my_mlx_pixel_put(mlx, x + mlx->player.x , y + mlx->player.y, 0xF93308);			
			x++;
		}
		y++;
	}
	draw_line(mlx, mlx->player.rotat_angle, mlx->player.x + 1, mlx->player.y + 1);
	return (0);
}

double ft_mod(double x, double y) {

    double div = x / y;
    double rounded = round(div);  
    double result = x - rounded * y;
    return result + 0.000001;
}
void	normalize_ray(t_mlx *mlx, int i, double ray_angle)
{
	// mlx->rays[i].ray_angle = fmod(ray_angle, PI * 2);
		// if (mlx->rays[i].ray_angle < 0 )
		// 	mlx->rays[i].ray_angle = PI * 2 + mlx->rays[i].ray_angle;
	    while (ray_angle < 0 && ray_angle >  -0.000001) {
		printf("mode : %lf\n", ray_angle);
        ray_angle += 2 * PI; // Add 2π to make it positive
    }
	// ray_angle = round(ray_angle);
    while (ray_angle >= 2 * PI ) {
        ray_angle -= 2 * M_PI; // Subtract 2π to bring it within range
    }
	mlx->rays[i].ray_angle  = ray_angle;
	
		printf("norm ray : %f\n", (mlx->rays[i].ray_angle * 180) / PI);
	mlx->rays[i].f_d = mlx->rays[i].ray_angle > 0 && mlx->rays[i].ray_angle < PI ? 1 : 0;
	mlx->rays[i].f_u = !mlx->rays[i].f_d;
	mlx->rays[i].f_r = mlx->rays[i].ray_angle > 1.5 * PI || mlx->rays[i].ray_angle < PI / 2 ? 1 : 0;
	mlx->rays[i].f_l = !mlx->rays[i].f_r;
	// printf("u : %d , d : %d r : %d, l : %d\n", mlx->rays[i].f_u, mlx->rays[i].f_d, mlx->rays[i].f_r, mlx->rays[i].f_l);
}
void	cast_rays(t_mlx *mlx)
{
	int	i;
	double ray_angle;

	i = 0;
	ray_angle = mlx->player.rotat_angle - (FOV / 2);
	static int s;
	while (i < 1)
	{
		// mlx->rays[i].ray_angle = ft_mod(ray_angle, PI * 2);
		// if (mlx->rays[i].ray_angle < 0)
		// printf("ray : %f\n", (ray_angle * 180)  / PI);
		// 	mlx->rays[i].ray_angle = PI * 2 + mlx->rays[i].ray_angle;
		normalize_ray(mlx, i, ray_angle);
		// printf("%f\n", mlx->rays[i].ray_angle);
		// draw_line(mlx, mlx->rays[i].ray_angle, mlx->player.x + 1, mlx->player.y + 1);
		get_intersect_and_draw(mlx, i);
		ray_angle += FOV / (mlx->win_w);
		i++;
	}
	i = 0;
	// // ray_angle = mlx->player.rotat_angle - (FOV / 2);
	while (i < 1)
	{
		// draw_line(mlx, mlx->rays[i].ray_angle, mlx->player.x + 1, mlx->player.y + 1);
		// printf("ray[%d]: %f\n", i, (mlx->rays[i].ray_angle * 180) / PI);
		
		draw_ray_line(mlx, mlx->rays[i].ray_angle, mlx->player.x, mlx->player.y, i);
		i++;
	}
	s = 1;
}
int	render_map(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_init, mlx->mlx_win);
	draw_map_img(mlx->map, mlx);
	draw_player(mlx);
	cast_rays(mlx);
	// get_horizontal_intersect(mlx);
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
		mlx->player.rotat_angle -= mlx->player.rot_speed;
	if (key == 124)
		mlx->player.rotat_angle += mlx->player.rot_speed;
	if (!check_wall(mlx, key))
		return (1);
	if (key == 13)
		move_up(mlx);
	if (key == 1)
		move_down(mlx);
	if (key == 0)
		move_left(mlx);
	if (key == 2)
		move_right(mlx);
	return (0);
}

void	init_player(t_mlx *mlx)
{
	mlx->player.rotat_angle = -90 * (PI / 180);
	mlx->player.rot_speed = 8 * (PI / 180);
	mlx->player.mov_speed = 8;
}
int	main()
{
	char map[14][13] = {
								{'1', '1' , '1' , '1' , '1', '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' } ,
								{'1', '0' , '0' , '0' , '1', '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' } ,
								{'1', '0' , '0' , '1' , '1', '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' } ,
								{'1', '0' , '0' , '0' , '1', '1' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '1', '1' , '0' , '0' , '0' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , 'N' , '1' , '1' , '0' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '1' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '1' , '0' , '0' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '0' , '1' , '0' , '0' , '1' } ,
								{'1', '1' , '1' , '1' , '1', '0' , '1' , '1' , '1' , '1' , '1' , '1' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '0' , '0' , '1' , '1' , '1' , '1' , '1' } ,
								{'1', '0' , '1' , '1' , '1', '1' , '0' , '1' , '1' , '1' , '1' , '1' , '1' } ,
								{'1', '0' , '0' , '0' , '0', '0' , '0' , '1' , '1' , '1' , '1' , '1' , '1' } ,
								{'1', '1' , '1' , '1' , '1', '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' }
							};
	t_mlx	*mlx;
	t_game	game;
	t_player player;
	char **arr;
	mlx->map = allocate_map(map, 14, 13);
	mlx->mlx_init = mlx_init();
	mlx->win_h = 14 * TILE_SIZE;
	mlx->win_w = 13 * TILE_SIZE;
	mlx->mlx_win = mlx_new_window(mlx->mlx_init, mlx->win_w, mlx->win_h, "cub3d");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_init, mlx->win_w, mlx->win_h);
	mlx->img.data = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size, &mlx->img.endian);
	mlx->rays = (t_ray *)malloc(sizeof(t_ray) * mlx->win_w);
	init_player(mlx);
	printf("%f\n", FOV);
	printf("%d\n", mlx->img.size);
	mlx_hook(mlx->mlx_win, 02, 0, move_player, mlx);
	mlx_loop_hook(mlx->mlx_init, render_map, mlx);
	mlx_loop(mlx->mlx_init);
	
}