/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:47:40 by adardour          #+#    #+#             */
/*   Updated: 2023/09/01 18:37:07 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../parsing/get_next_line/get_next_line.h"
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

# define DISPLAY_ERROR "The map must be closed/surrounded by walls: "
# define DISPLAY_ERROR1 "There are some elements missing: "
# define DISPLAY_ERROR2 "Color not valid; expected format (R-G-B): "

typedef struct t_help
{
	char	**spliting;
	int		i;
	int		j;
	int		count;
}	t_help;

typedef struct s_text
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_text;

typedef struct s_floor
{
	char			*r;
	char			*g;
	char			*b;
	unsigned int	color;
}				t_floor;

typedef struct s_ceiling
{
	char			*r;
	char			*g;
	char			*b;
	unsigned int	color;
}				t_ceiling;

typedef struct s_data
{
	t_ceiling	ceiling;
	t_floor		floor;
	t_text		texture;
	char		**map_represent;
	void		*init;
}				t_data;

typedef struct s_vars
{
	void		*mlx_ptr;
	void		*mlx_win;
	int			width;
	int			height;
	t_data		*data;
}				t_vars;

char			*ft_strchr(char *s, int c);
const char		*ft_strstr(const char *haystack, const char *needle);
char			**ft_split(char *str, int del);
char			*ft_strdup(char *s1);
int				ft_atoi(const char *str);
void			free_things(char **spliting);
int				parse_map(t_data *data, int reached_map, char *path);
int				parse_element(t_data *data);
char			*get_begin(int reached_map, int fd);
int				parse_element(t_data *data);
int				check_spaces(char *line);
int				fill(int fd, t_data *data, int count, char *start_map);
int				check_map(char **represent_map);
void			check_symbols(char **represent_map);
void			complete_the_map(int longest_length, t_data *data);
int				get_longest_length(char **represent_map);
void			check_characters(char *line, int *w, int *e, int *o);
int				get_columns(char **represent);
int				get_rows(char **represent);
unsigned int	get_color(char *r, char *g, char *b);
int				colors(t_data *data);
int				check_rgbs(t_ceiling ceiling, t_floor floor);
int				check_color(char *color);
int				check_car(char *r, char *g, char *b);
char			*ft_substr(char *s, unsigned int start, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strrchr(char *s, int c);
char			*ft_strtrim(char *s1, char *set);
int				open_file(char *filename);
void			open_texture(char *n, char *s, char *w, char *e);
unsigned int	get_color(char *r, char *g, char *b);
void			check_last_line(char **map_represent, int index_last);
int				put_data(t_data *data, int fd, int *reached_map);
int				put_rgb(t_data *data, char *line, char identifier);
int				put(char *line, t_data *data, char i);
int				check_cub(char *path);
#endif