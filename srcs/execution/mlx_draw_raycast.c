/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:11:35 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/19 08:26:02 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_wall_textures(t_map *map, t_mlx *texture, int x)
{
	int				y;
	int				texy;
	int				texx;
	double			step;
	double			texpos;

	y = map->ray->drawstart;
	step = 1.0 * 64 / map->ray->line_height;
	texpos = (map->ray->drawstart - WIN_Y / 2 + map->ray->line_height / 2)
		* step;
	texx = (int)(map->ray->wallhit * (double)(texture->x));
	texx = texture->x - texx - 1;
	while (y < map->ray->drawend)
	{
		texy = (int)texpos & (64 - 1);
		texpos += step;
		ft_pixel_drawing(map->mlx, x, y, \
			ft_get_pixel_color(texture, texx, texy));
		y++;
	}
}

/**
 * @brief draw_walls: 
*/
void	draw_walls(t_map *map, int x)
{
	if (map->ray->side == 1)
	{
		if (map->ray->stepy > 0)
			draw_wall_textures(map, map->texture->south, x);
		else
			draw_wall_textures(map, map->texture->north, x);
	}
	else if (map->ray->side == 0)
	{
		if (map->ray->stepx < 0)
			draw_wall_textures(map, map->texture->east, x);
		else
			draw_wall_textures(map, map->texture->west, x);
	}
}

void	draw_roof_floor(t_map *map, int x)
{
	int	y;

	y = 0;
	while (y < (int)WIN_Y)
	{
		if (y >= map->ray->drawend)
			ft_pixel_drawing(map->mlx, x, y, map->texture->floor);
		else if (y <= map->ray->drawstart)
			ft_pixel_drawing(map->mlx, x, y, map->texture->roof);
		y++;
	}
}

void	raydrawing(t_map *map)
{
	int	x;

	x = 0;
	while (x < (int)WIN_X)
	{
		raycast_1(map, x);
		draw_roof_floor(map, x);
		draw_walls(map, x);
		x++;
	}
	minimap(map);
	mlx_put_image_to_window(map->mlx->mlx_ptr, map->mlx->win_ptr,
		map->mlx->img_to_window, 0, 0);
}
