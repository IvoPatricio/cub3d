/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_of_mlx.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:22:35 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/18 00:00:18 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_alloc_textures_utils(t_map *map, t_mlx *texture, char *path)
{
	texture->img_to_window = mlx_xpm_file_to_image(map->mlx->mlx_ptr, path, \
		&texture->x, &texture->y);
	texture->buffer = mlx_get_data_addr(texture->img_to_window, &texture->a, \
		&texture->b, &texture->c);
}

void	ft_init_alloc_textures(t_map *map)
{
	t_texture   *texture;

	texture = map->texture;
	texture->north = malloc(sizeof(t_mlx));
	ft_alloc_textures_utils(map, texture->north, texture->n);
	texture->south = malloc(sizeof(t_mlx));
	ft_alloc_textures_utils(map, texture->south, texture->s);
	texture->west = malloc(sizeof(t_mlx));
	ft_alloc_textures_utils(map, texture->west, texture->w);
	texture->east = malloc(sizeof(t_mlx));
	ft_alloc_textures_utils(map, texture->east, texture->e);
}
