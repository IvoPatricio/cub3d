# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 11:57:44 by mrudloff          #+#    #+#              #
#    Updated: 2023/07/24 20:23:00 by ifreire-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
CC			= gcc -fsanitize=address -g
CFLAGS		= -I/usr/include -Imlx_linux -O3
SRC			= main.c
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


