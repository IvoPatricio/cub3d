/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_angle_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:11:32 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/19 07:31:49 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief ft_destroy_images_display_free: Destroys all the images 
 * allocated on the mlx and the display of mlx also freeing the
 * textures->mlx of walls
*/
void	ft_destroy_images_display_free(t_map *map)
{
	mlx_destroy_image(map->mlx->mlx_ptr, map->mlx->img_to_window);
	mlx_destroy_image(map->mlx->mlx_ptr, map->texture->north->img_to_window);
	mlx_destroy_image(map->mlx->mlx_ptr, map->texture->south->img_to_window);
	mlx_destroy_image(map->mlx->mlx_ptr, map->texture->east->img_to_window);
	mlx_destroy_image(map->mlx->mlx_ptr, map->texture->west->img_to_window);
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

/**
 * @brief ft_destroyer: destroys the window of mlx, calls the function
 * that destroys the mlx images, frees the mlx_ptr, and frees the whole
 * project afterwards
*/
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
	double	old_plane_x;
	double	old_dir_x;
	t_play	*play;

	play = map->play;
	old_dir_x = play->dir_x;
	play->dir_x = play->dir_x * cos(rotate) - play->dir_y * sin(rotate);
	play->dir_y = old_dir_x * sin(rotate) + play->dir_y * cos(rotate);
	old_plane_x = play->plane_x;
	play->plane_x = play->plane_x * cos(rotate) - play->plane_y * sin(rotate);
	play->plane_y = old_plane_x * sin(rotate) + play->plane_y * cos(rotate);
}
