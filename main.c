/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:39:08 by aalami            #+#    #+#             */
/*   Updated: 2023/08/30 17:57:41 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub.h"
#include "./include/parsing.h"

void	init(t_data *data)
{
	data->texture.ea = NULL;
	data->texture.so = NULL;
	data->texture.no = NULL;
	data->texture.we = NULL;
	data->ceiling.b = NULL;
	data->ceiling.r = NULL;
	data->ceiling.g = NULL;
	data->floor.b = NULL;
	data->floor.r = NULL;
	data->floor.g = NULL;
}

void	fill_text_arr(t_mlx *mlx, t_texture *text, int *text_arr)
{
	char	*dst;
	int		color;
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 0;
	y = 0;
	while (y < text->h * text->img.size)
	{
		x = 0;
		while (x < text->w)
		{
			dst = text->img.data + (y + x * (text->img.bpp / 8));
			text_arr[i] = *(unsigned int *)dst;
			i++;
			x++;
		}
		y += text->img.size;
	}
}

void	free_map(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mlx->win_h / TILE_SIZE)
	{
		free(mlx->map[i]);
		i++;
	}
	free(mlx->map);
}

int	ft_exit(t_mlx *mlx)
{
	free(mlx->rays);
	free_map(mlx);
	mlx_destroy_window(mlx->mlx_init, mlx->mlx_win);
	free(mlx);
	exit (0);
	return (0);
}
void leak()
{
	system("leaks cub3d");
}
int	main(int argc, char **argv)
{
	t_data	*data;
	t_mlx	*mlx;
	int		fd;
	int		reached_map;
// atexit(leak);
	if (argc != 2)
		return (printf("Usage: ./program_name file_name\n"));
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		return (printf("Malloc error\n"));
	mlx->mlx_init = mlx_init();
	reached_map = 0;
	fd = open(argv[1], O_RDWR, 0777);
	if (fd == -1)
		return (printf("Error opening file\n"));
	data = malloc(sizeof(t_data));
	init(data); 
	mlx->data = data;
	if (!data || parsing(argv, reached_map, fd, mlx))
		return (printf("Error parsing\n"));
	drawing(mlx, data);
	return (0);
}
