# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboute <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/04 20:02:22 by nboute            #+#    #+#              #
#    Updated: 2017/10/03 19:13:33 by nboute           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: make all clean fclean re

NAME = Wolf3D

LIB = -L libft/ -lft

LIBFT = libft/libft.a

MLX = -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit

LIBMLX = minilibx_macos/mlx.a


PTHREAD = -lpthread -D_REENTRANT

CFLAGS = -c -Wall -Wextra -Werror

OPTI = -O3 -march=native

WFLAGS = -Wall -Wextra -Werror

CC = gcc

C_DIR = src/

SRCS = raycasting_basics.c \
	   maze.c \
	   loadbmp.c \
	   maps.c \
	   slide.c \
	   ft_load_screen.c \
	   load_textures.c \
	   new_struct.c
#	 move.c

SRC = $(addprefix $(C_DIR), $(SRCS))

OBJ = $(SRCS:.c=.o)

INC = -I includes -I libft/

all : $(LIBMLX) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(MLX) $^ -o $@ $(LIB)

$(LIBFT):
	make -C libft/

$(LIBMLX):
	make -C minilibx_macos/

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) $^ $(INC)

clean :
	make clean -C libft/
	make clean -C minilibx_macos/
	rm -f $(OBJ)

fclean : clean
	rm -f $(LIBFT)
	rm -f $(LIBMLX)
	rm -f libft.a
	rm -f $(NAME)

re : fclean all
