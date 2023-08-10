/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:00:25 by aalami            #+#    #+#             */
/*   Updated: 2023/08/10 20:22:10 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>

void	get_horizontal_intersect(t_mlx *mlx, int i)
{
	double y_intersect;
	double x_intersect;
	double y_step;
	double x_step;

	
	y_step = TILE_SIZE;
	y_step *= mlx->rays[i].f_d ? 1 : -1;
	x_step = y_step / (tan(mlx->rays[i].ray_angle));
	x_step *= (mlx->rays[i].f_r && x_step < 0) ? -1 : 1;
	x_step *= (mlx->rays[i].f_l && x_step > 0) ? -1 : 1;
		// printf("Xstep = %lf ; Ystep = %lf       %f\n", x_step, y_step, (mlx->rays[i].ray_angle) );
	y_intersect = floor(mlx->player.y / TILE_SIZE) * TILE_SIZE;
	y_intersect += mlx->rays[i].f_d ? TILE_SIZE : 0;
	x_intersect = mlx->player.x + ((y_intersect - mlx->player.y ) / tan(mlx->rays[i].ray_angle));
		// printf("mlx->player.x = %lf ;      mlx->player.y = %lf    ;   y_intersect = %lf   tan(mlx->rays[i].ray_angle) = %lf\n", mlx->player.x, mlx->player.y , y_intersect, fabs(tan(mlx->rays[i].ray_angle)));
	
		// printf("HORIZONTAL\n");
		// printf("x_b = %lf ;      y_b = %lf    ;   ray_angle = %lf \n", x_intersect, (y_intersect) , mlx->rays[i].ray_angle);

	 while ((int)y_intersect / TILE_SIZE >= 0 && (int)y_intersect / TILE_SIZE < mlx->win_h / TILE_SIZE && 
		(int)x_intersect / TILE_SIZE >= 0 && (int)x_intersect / TILE_SIZE < mlx->win_w / TILE_SIZE  && mlx->map[(int)((y_intersect + (mlx->rays[i].f_u ? -1 : 1 )) / TILE_SIZE)][(int)((x_intersect) / TILE_SIZE)] != '1')
	{
		y_intersect += ( y_step);
		x_intersect += (x_step) ;
	}
	// 	printf("x_e = %f ; y_e = %f\n", (x_intersect) , (y_intersect) );
	// printf("x_i in map : %d , y_i in map : %d\n", (int)x_intersect / TILE_SIZE, (int)y_intersect / TILE_SIZE);
	// if ((int)y_intersect / TILE_SIZE >= 0 && (int)y_intersect / TILE_SIZE < mlx->win_h / TILE_SIZE && 
	// 	(int)x_intersect / TILE_SIZE >= 0 && (int)x_intersect / TILE_SIZE < mlx->win_w / TILE_SIZE)
	// {
    	mlx->rays[i].h_intersec_x = x_intersect;
    	mlx->rays[i].h_intersec_y = y_intersect ;
		// printf("dx = %f ; dy = %f\n", dx, dy);
		double dy = ((y_intersect ) - mlx->player.y ) ;
		double dx = ((x_intersect ) - mlx->player.x) ;
		mlx->rays[i].dis =  sqrt(dx * dx + dy * dy);
	// }
	// else
	// 	mlx->rays[i].dis =  0;
		
	// printf("dis hor %f\n", mlx->rays[i].dis);
}
void    get_vertical_intersect(t_mlx *mlx, int i)
{
    double y_intersect;
	double x_intersect;
	double y_step;
	double x_step;
    x_step = TILE_SIZE;
	x_step *= mlx->rays[i].f_r ? 1 : -1;
	y_step = x_step * tan(mlx->rays[i].ray_angle);
	y_step *= (mlx->rays[i].f_d && y_step < 0) ? -1 : 1;
	y_step *= (mlx->rays[i].f_u && y_step > 0) ? -1 : 1;
	x_intersect = floor(mlx->player.x / TILE_SIZE) * TILE_SIZE;
	x_intersect += mlx->rays[i].f_r ? TILE_SIZE : 0;
	y_intersect = (mlx->player.y + ((x_intersect - mlx->player.x) * tan(mlx->rays[i].ray_angle)));
		// printf("VERTICAL\n");
		// printf("VERTICAL x_b = %f ; y_b = %f\n", x_intersect, y_intersect);
		printf("1111 = %d\n", ((int)(((x_intersect) )/ TILE_SIZE)));
    while ((int)y_intersect / TILE_SIZE >= 0 && (int)y_intersect / TILE_SIZE < mlx->win_h / TILE_SIZE && 
		(int)x_intersect / TILE_SIZE >= 0 && (int)x_intersect / TILE_SIZE < mlx->win_w / TILE_SIZE  && mlx->map[(int)((y_intersect) / TILE_SIZE)][(int)(((x_intersect) + (mlx->rays[i].f_l ? -1 : 1 ))/ TILE_SIZE)] != '1')
	{
		y_intersect += ( y_step) ;
		x_intersect += (x_step);
	}
		// printf("x_e = %d ; y_e = %d     c=%c\n", ((int)(((x_intersect) + (mlx->rays[i].f_l ? -1 : 1 ))/ TILE_SIZE)), (int)(y_intersect) / TILE_SIZE, mlx->map[(int)((y_intersect) / TILE_SIZE)][(int)(((x_intersect) + (mlx->rays[i].f_l ? -1 : 1 ))/ TILE_SIZE)]);
	// if ((int)y_intersect / TILE_SIZE >= 0 && (int)y_intersect / TILE_SIZE < mlx->win_h / TILE_SIZE && 
	// 	(int)x_intersect / TILE_SIZE >= 0 && (int)x_intersect / TILE_SIZE < mlx->win_w / TILE_SIZE )
	// {
    	 mlx->rays[i].v_intersec_x = x_intersect ;
    	mlx->rays[i].v_intersec_y = y_intersect ;
		double dx = ((x_intersect ) - mlx->player.x);
		double dy = (y_intersect  - mlx->player.y );
    	if (sqrt(dx * dx + dy * dy) < mlx->rays[i].dis)
        mlx->rays[i].dis = sqrt(dx * dx + dy * dy);
	// }
	// else
	// {
	// 	if ((int)mlx->rays[i].h_intersec_y / TILE_SIZE < 0 || (int)mlx->rays[i].h_intersec_y / TILE_SIZE >= mlx->win_h / TILE_SIZE ||
	// 	(int)mlx->rays[i].h_intersec_x / TILE_SIZE < 0 || (int)mlx->rays[i].h_intersec_x / TILE_SIZE >= mlx->win_w / TILE_SIZE)
    //    		mlx->rays[i].dis = 0;
	// }
}
void    get_intersect_and_draw(t_mlx *mlx, int i)
{
	static int it;
	
	if (it == 0)
   	{
		get_horizontal_intersect(mlx, i);
		
   	 	get_vertical_intersect(mlx, i);
		// it = 1;
	} 
    
    // draw_ray_line(mlx, mlx->rays[i].ray_angle, mlx->player.x + 1, mlx->player.y + 1, i);
}