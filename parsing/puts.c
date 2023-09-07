/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:48:05 by adardour          #+#    #+#             */
/*   Updated: 2023/09/07 16:16:34 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/cub.h"

void	put_things(t_data *data, char	**spliting, int flags)
{
	if (spliting[3])
	{
		printf("color not valid\n");
		exit(1);
	}
	if (flags == 0)
	{
		data->floor.g = ft_strdup(spliting[1]);
		data->floor.b = ft_strdup(spliting[2]);
	}
	else
	{
		data->ceiling.g = ft_strdup(spliting[1]);
		data->ceiling.b = ft_strdup(spliting[2]);
	}
}

int	check_identifier(char *line)
{
	char	**spliting;

	spliting = ft_split(line, ' ');
	printf("%s\n",spliting[0]);
	// if (spliting[0] != NULL && spliting[1] != NULL)
	// {
	// 	if (spliting[0][0] == 'S' && spliting[0][1] != 'O' \
	// 	&& spliting[0][1] != '\0')
	// 		return (free_things(spliting), 0);
	// 	else if (spliting[0][0] == 'W' && spliting[0][1] != 'E' \
	// 	&& spliting[0][1] != '\0')
	// 		return (free_things(spliting), 0);
	// 	else if (spliting[0][0] == 'E' && spliting[0][1] != 'A' \
	// 	&& spliting[0][1] != '\0')
	// 		return (free_things(spliting), 0);
	// 	else if (spliting[0][0] == 'N' \
	// 	&& spliting[0][1] != 'O' \
	// 	&& spliting[0][1] != '\0')
	// 		return (free_things(spliting), 0);
	// 	else if (spliting[0][0] == 'C' && spliting[0][1] != '\0')
	// 		return (free_things(spliting), 0);
	// 	else if (spliting[0][0] == 'F' && spliting[0][1] != '\0')
	// 		return (free_things(spliting), 0);
	// }
	free_things(spliting);
	return (1);
}

int	count_color(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count > 2)
		return (0);
	return (1);
}

void	put_color(char *color, int flag,char *identifier, t_data *data)
{
	if(ft_strlen(color) == 0)
		return ;
	if (!ft_strcmp(identifier, "F"))
	{
		if (flag == 0)
			data->floor.r = ft_strtrim(color,"\n");
		else if (flag == 1)
			data->floor.g = ft_strtrim(color,"\n");
		else
			data->floor.b = ft_strtrim(color,"\n");
	}
	else
	{
		if (flag == 0)
			data->ceiling.r = ft_strtrim(color,"\n");
		else if (flag == 1)
			data->ceiling.g = ft_strtrim(color,"\n");
		else
			data->ceiling.b = ft_strtrim(color,"\n");
	}
}

void	put_celing_floor(char *line,char *identifier,t_data *data)
{
	char **spliting;
	static int flag;

	flag = 0;
	int start;
	int j;
	spliting = ft_split(line, ' ');
	int i;
	char *color;
	i = 1;
	start = 0;
	while (spliting[i])
    {
		int j;
		j = 0;
		while (spliting[i][j])
		{			
			if (spliting[i][j] == ',' && spliting[i][j] != '\0')
			{   
				color = ft_substr(spliting[i], start, j - start);
				put_color(color, flag, identifier, data);
				free(color);
				flag++;
				j++;
			}
			start = j;
			while (spliting[i][j] && spliting[i][j] != ',')
				j++;
		}
		if (start != j)
		{
				color = ft_substr(spliting[i], start, j - start);
				put_color(color, flag, identifier, data);
				free(color);
		}
		i++;
    }
	free_things(spliting);
}

int	just_check(char *color)
{
	int i;
	i = 0;
	while (color[i])
	{
		if (color[i] < 48 || color[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int	put_rgb(t_data *data, char *line, char *identifier)
{
	int i;
	char **spliting;
	char *str;
	char *trim;
	
	i = 0;
	str = ft_strchr(line, identifier[0]) + 1;
	while (str[i] && str[i] == ' ')
		i++;
	i = 0;
	spliting = ft_split(str, ',');
	while (spliting[i])
	{
		trim = ft_strtrim(spliting[i]," \n");
		if (!just_check(trim))
		{
			free(trim);
			free_things(spliting);
			return (0);
		}
		free(trim);
		i++;
	}
	free_things(spliting);
	if (i != 3)
		return (0);
	put_celing_floor(line, identifier, data);
	return (1);
}

int	put_data(t_data *data, int fd, int *reached_map)
{
	char		*line;
	char		**spliting;
	static int 	flags;

	line = get_next_line(fd);
	while (line != NULL)
	{
		spliting = ft_split(line, ' ');
		if (!ft_strcmp(spliting[0], "SO") || 
		!ft_strcmp(spliting[0], "WE") || 
		!ft_strcmp(spliting[0], "EA")  || 
		!ft_strcmp(spliting[0], "NO") )
		{
			put(line, data);
			(*reached_map)++;
		}
		else if (!ft_strcmp(spliting[0], "\n"))
			(*reached_map)++;
		else if (!ft_strcmp(spliting[0], "F") ||
		!ft_strcmp(spliting[0], "C"))
		{
			put_rgb(data, line, spliting[0]);
			(*reached_map)++;
		}
		free(line);
		free_things(spliting);
		line = get_next_line(fd);
	}
	if (*reached_map < 6)
		return (0);
	return (1);
}
