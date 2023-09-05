NAME = cub3d


SOURCES =  main.c ./execution/intersection.c ./execution/wall_render.c ./execution/ray_casting.c ./execution/ray_casting_utils.c ./execution/player.c ./execution/render_mini_map.c ./execution/intersection_utils.c ./execution/render_elements.c ./execution/wall_render_utils.c \
./parsing/get_next_line/get_next_line.c ./parsing/get_next_line/get_next_line_utils.c \
./parsing/utils/ft_strchr.c ./parsing/utils/ft_strstr.c ./parsing/utils/ft_split.c ./parsing/utils/ft_strdup.c ./parsing/utils/ft_atoi.c \
./parsing/utils/free_data.c ./parsing/utils/ft_substr.c ./parsing/utils/ft_strcmp.c ./parsing/utils/ft_strrchr.c \
./parsing/cub3d.c ./parsing/get_lines.c ./parsing/parse_element.c ./parsing/puts.c ./parsing/parse_map.c ./parsing/fill.c ./parsing/check_map.c ./parsing/complete_map.c \
./parsing/check_caracteres.c ./parsing/rows_and_columns.c ./parsing/colors.c  ./parsing/strtrim.c \
./handle_files/open.c \
./drawing.c ./parsing/parsing.c ./parsing/get_color.c ./parsing/put.c ./parsing/get_x_y.c ./parsing/textures.c ./parsing/check_cub.c  \
./check/check.c \

OBJ = $(SOURCES:.c=.o)
MLX_DIR = mlx
CC = cc
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) ${CFLAGS} $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME) 

%.o: %.c ./include/cub.h  ./include/parsing.h 
	$(CC) ${CFLAGS} -O3 -Imlx -c $< -o $@

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)
	

re: fclean all