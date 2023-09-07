/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:39:08 by aalami            #+#    #+#             */
/*   Updated: 2023/09/07 16:16:42 by aalami           ###   ########.fr       */
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
	data->map_represent = NULL;
}

void	fill_text_arr(t_texture *text, int *text_arr)
{
	char	*dst;
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
	int	h;

	i = 0;
	j = 0;
	h = get_rows(mlx->map);
	while (i < h)
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
	free_data(mlx->data);
	mlx_destroy_window(mlx->mlx_init, mlx->mlx_win);
	free(mlx);
	exit (0);
}
void	a()
{
	system("leaks cub3d");
}
int	main(int argc, char **argv)
{
	t_data	*data;
	int		fd;
	int		reached_map;

	atexit(a);
	if (argc != 2 || !check_cub(argv[1]))
		return (printf("Usage: ./program_name file_name\n"));
	reached_map = 0;
	fd = open(argv[1], O_RDWR, 0777);
	if (fd == -1)
		return (printf("Error opening file\n"));
	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("");
		return (1);
	}
	init(data); 
	if (parsing(argv, reached_map, fd, data))
	{
		printf("error parsing\n");
		exit (1);
	}
	data->init = mlx_init();
	// drawing(data);
	return (0);
}
