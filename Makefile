# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 11:57:44 by mrudloff          #+#    #+#              #
#    Updated: 2023/08/08 22:55:18 by ifreire-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
CC			= gcc #-fsanitize=address -g
CFLAGS		= -I/usr/include -Imlx_linux -O3
SRC			= srcs/main.c \
			srcs/parse/init.c \
			srcs/parse/main_parse.c \
			srcs/parse/ft_split.c \
			srcs/parse/parse_utils.c \
			srcs/parse/printf_utils.c \
			srcs/parse/free_utils.c \
			srcs/parse/rgb_path_parse.c \
			srcs/parse/get_next_line/get_next_line.c \
			srcs/parse/get_next_line/get_next_line_utils.c
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

.PHONY: all clean fclean re

#    make re && clear && valgrind -s --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./cub3d ./maps/map1.cub

