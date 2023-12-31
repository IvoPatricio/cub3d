# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 11:57:44 by mrudloff          #+#    #+#              #
#    Updated: 2023/08/19 07:37:45 by ifreire-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
CC			= gcc -Wall -Wextra -Werror #-fsanitize=address -g
CFLAGS		= -I/usr/include -Imlx_linux -O3
SRC			= srcs/main.c \
			srcs/parse/main_parse.c \
			srcs/parse/parse_file.c \
			srcs/parse/parse_map_caracthers.c \
			srcs/parse/parse_map_flood_fill.c \
			srcs/parse/parse_path_data.c \
			srcs/parse/parse_path_file.c \
			srcs/utils/utils_malloc.c \
			srcs/utils/libft/utils_parse_1.c \
			srcs/utils/libft/utils_parse_2.c \
			srcs/utils/libft/ft_split.c \
			srcs/utils/utils_printf.c \
			srcs/utils/utils_free.c \
			srcs/utils/get_next_line/get_next_line.c \
			srcs/utils/get_next_line/get_next_line_utils.c \
			srcs/execution/init_rgb.c \
			srcs/execution/init_textures_of_mlx.c \
			srcs/execution/init_textures_player.c \
			srcs/execution/mlx_angle_close.c \
			srcs/execution/mlx_draw_raycast.c \
			srcs/execution/mlx_keys.c \
			srcs/execution/mlx_put_pixel.c \
			srcs/execution/mlx_draw_minimap.c \
			srcs/execution/raycast_lodev_dda.c
OBJ			= $(SRC:.c=.o)
MLX_PATH	= ./mini-linux

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_NAME):
	@${MAKE} -C $(MLX_PATH)

$(NAME): $(OBJ)
	@${MAKE} -C $(MLX_PATH)
	$(CC) $(OBJ) -Lmini-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	@${MAKE} clean -C $(MLX_PATH)
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all


r:
	make && ./cub3d maps/map1.cub


.PHONY: all clean fclean re

#    make re && clear && valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./cub3d ./maps/map1.cub

