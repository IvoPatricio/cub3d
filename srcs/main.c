/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:22:25 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/19 12:38:16 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_hook(t_map *map)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(map->mlx->mlx_ptr, map->mlx->win_ptr, &x, &y);
	if (x != map->mousex)
	{
		if (x >= ((WIN_X / 2) + ((int)MOUSE_SPEED * 10)) \
			&& (map->data->direction == NORTH || map->data->direction == SOUTH))
			ft_key_angle(map, (double)ROTATE_SPEED);
		else if (x >= ((WIN_X / 2) + ((int)MOUSE_SPEED * 10)))
			ft_key_angle(map, -(double)ROTATE_SPEED);
		if (x <= ((WIN_X / 2) - ((int)MOUSE_SPEED * 10)) \
			&& (map->data->direction == NORTH || map->data->direction == SOUTH))
			ft_key_angle(map, -(double)ROTATE_SPEED);
		else if (x <= ((WIN_X / 2) - ((int)MOUSE_SPEED * 10)))
			ft_key_angle(map, (double)ROTATE_SPEED);
		map->mousex = x;
	}
	mlx_mouse_move(map->mlx->mlx_ptr, map->mlx->win_ptr, (int)WIN_X / 2,
		(int)WIN_Y / 2);
	raydrawing(map);
	return (0);
}

void	ft_mlx_init(t_map *map)
{
	map->mousex = (int)WIN_X / 2;
	map->mlx->mlx_ptr = mlx_init();
	if (map->mlx->mlx_ptr != 0)
	{
		ft_init_alloc_textures(map);
		map->mlx->win_ptr = mlx_new_window(map->mlx->mlx_ptr, (int)WIN_X, \
			(int)WIN_Y, "3D");
		map->mlx->img_to_window = mlx_new_image(map->mlx->mlx_ptr, (int)WIN_X, \
			(int)WIN_Y);
		map->mlx->buffer = mlx_get_data_addr(map->mlx->img_to_window, \
			&map->mlx->a, &map->mlx->b, &map->mlx->c);
		if (!map->mlx->buffer)
		{
			printf("Error\nMlx_Buffer Allocation Failed");
			free_structs_mlx(map);
		}
		mlx_mouse_hide(map->mlx->mlx_ptr, map->mlx->win_ptr);
		mlx_loop_hook(map->mlx->mlx_ptr, mouse_hook, map);
		raydrawing(map);
		mlx_do_key_autorepeaton(map->mlx->mlx_ptr);
		mlx_hook(map->mlx->win_ptr, 2, 1, ft_keys, map);
		mlx_hook(map->mlx->win_ptr, 17, 1L << 17, ft_destroyer, map);
		mlx_hook(map->mlx->win_ptr, 33, 1L << 17, ft_destroyer, map);
		mlx_loop(map->mlx->mlx_ptr);
	}
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 2)
	{
		map.data = malloc(sizeof(t_data));
		struct_malloc_error(&map, map.data, sizeof(map.data));
		main_parse(map.data, argv);
		init_structs(&map);
		printf_map(map.data);
		printf_struct_map(&map);
		ft_mlx_init(&map);
		free_structs_mlx(&map);
	}
	else
	{
		printf("\e[1;31mERROR\n\e[0;0m");
		return (printf("The Number Of Arguments Must Be Only TWO"));
	}
}
