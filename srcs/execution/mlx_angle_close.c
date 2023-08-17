/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_angle_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:11:32 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 23:18:13 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void ft_destroy_images_display_free(t_map *map)
{
	mlx_destroy_image(map->mlx->mlx_ptr, map->mlx->img_to_window);
	mlx_destroy_image(map->mlx->mlx_ptr ,map->texture->north->img_to_window);
	mlx_destroy_image(map->mlx->mlx_ptr ,map->texture->south->img_to_window);
	mlx_destroy_image(map->mlx->mlx_ptr ,map->texture->east->img_to_window);
	mlx_destroy_image(map->mlx->mlx_ptr ,map->texture->west->img_to_window);
	mlx_destroy_display(map->mlx->mlx_ptr);
	if (map->texture->north)
		free(map->texture->north);
	if (map->texture->south)
		free(map->texture->south);
	if (map->texture->east)
		free(map->texture->east);
	if (map->texture->west)
		free(map->texture->west);
}

int	ft_destroyer(t_map *map)
{
	mlx_destroy_window(map->mlx->mlx_ptr, map->mlx->win_ptr);
	ft_destroy_images_display_free(map);
	free(map->mlx->mlx_ptr);
	free_structs_mlx(map);
	exit(1);
}

void	ft_key_angle(t_map *map, double rotate)
{
	t_play	*play;
	double	old_dir_x;
	double	old_plane_x;

	play = map->play;
	old_dir_x = play->dir_x;
	play->dir_x = play->dir_x * cos(rotate) - play->dir_y * sin(rotate);
	play->dir_y = old_dir_x * sin(rotate) + play->dir_y * cos(rotate);
	old_plane_x = play->plane_x;
	play->plane_x = play->plane_x * cos(rotate) - play->plane_y * sin(rotate);
	play->plane_y = old_plane_x * sin(rotate) + play->plane_y * cos(rotate);
	printf_struct_player(play);
}