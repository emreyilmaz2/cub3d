NAME = cub3d
LFLAGS = -framework OpenGL -framework AppKit
SRCS = main/*.c utils/*.c
GNL = get_next_line/get_next_line.a
CC = gcc -g

all: MINILIBX $(NAME)

$(GNL):
	make -C get_next_line
	@echo "GNL compiled !"

$(NAME):
	$(CC) $(LFLAGS) $(SRCS) $(GNL) -o $(NAME) mlx/libmlx.a

MINILIBX:
	make -C mlx --silent
	@echo "MINILIBX compiled !"

clean:
	rm -rf $(NAME)

re: clean all
