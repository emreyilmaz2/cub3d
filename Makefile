NAME = cub3d
LFLAGS = -framework OpenGL -framework AppKit
SRCS = main/*.c utils/*.c
GNL = get_next_line/get_next_line.a
LIBFT = libft/libft.a
CC = gcc -g

all: MINILIBX $(NAME)

$(LIBFT):
	make -C libft
	@echo "libft compiled !"

$(GNL):
	make -C get_next_line
	@echo "GNL compiled !"

$(NAME):
	$(CC) $(LFLAGS) $(SRCS) $(GNL) $(LIBFT) -o $(NAME) mlx/libmlx.a

MINILIBX:
	make -C mlx --silent
	@echo "MINILIBX compiled !"

clean:
	rm -rf $(NAME)

re: clean all
er: clean all
