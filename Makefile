NAME = cub3d


SOURCES = cub.c intersection.c wall_render.c





OBJ = $(SOURCES:.c=.o)
MLX_DIR = mlx
CC = cc
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ)  $(CFLAGS)   -lmlx -framework OpenGL -framework AppKit -o $(NAME) 



%.o: %.c cub.h 
	$(CC)  -Imlx -c $< -o $@

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)
	

re: fclean all