NAME = cub3d


SOURCES = cub.c intersection.c wall_render.c ray_casting.c ray_casting_utils.c player.c render_mini_map.c


OBJ = $(SOURCES:.c=.o)
MLX_DIR = mlx
CC = cc
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ)  $(CFLAGS)   -lmlx -framework OpenGL -framework AppKit -o $(NAME) 



%.o: %.c cub.h 
	$(CC)  -O3 -Imlx -c $< -o $@

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)
	

re: fclean all