# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 12:28:00 by yasinsensoy       #+#    #+#              #
#    Updated: 2023/05/04 18:08:40 by emyilmaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS = $(shell uname)
ifeq ($(OS), Darwin)
MINILIBX = minilibx
CFLAGS = -lmlx -framework OpenGL -framework AppKit -L ./$(MINILIBX)
else
MINILIBX = mlx
CFLAGS	:= -Wall -Werror -Wextra -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -L ./$(MINILIBX)
endif
NAME = Cub3d
SRC = $(wildcard src/*.c) $(wildcard get_next_line/*.c) libft/libft.a
CC = gcc
OBJ = $(SRC: .c = .o)

$(NAME): $(OBJ)
	@cd libft && make && cd ..
	@cd $(MINILIBX) && make && cd ..
	$(CC) $(SRC) $(CFLAGS) -o Cub3d
	@echo "\033[1;92mCOMPILING SUCCESSFUL\033[0m"

all : $(NAME)

clean:
	@rm -rf Cub3d
	@echo "\033[1;92mCLEANING DONE\033[0m"

fclean:
	@echo "\033[1;92mFCLEAN\033[0m"
	@make clean

re:
	@cd libft && make re && cd ..
	@cd $(MINILIBX) && make re && cd ..
	@echo "\033[1;92mREMAKE\033[0m"
	@make fclean
	@make

#get_next_line/get_next_line.c get_next_line/get_next_line_utils.c ./libft/libft.a

#NAME = Cub3d
# CC = gcc
# CLAFGS = -Wall -Wextra -Werror
# SRCS = $(wildcard *.c)
# OBJ = $(SRCS:.c = .o)

# $(NAME): $(OBJ)
# 	@$(CC) $(CLAFGS) $(SRCS) -o $(NAME)
# 	@echo "\033[1;92mCompiled succesfully..\033[0m"

# all: $(NAME)

# clean:
# 	rm -rf  $(NAME)

# fclean: clean


# re: fclean all

# .PHONY: all clean fclean re
