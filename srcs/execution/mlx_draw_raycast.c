/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:11:35 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 23:28:00 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_wall_textures(t_map *map, t_mlx *texture, int x)
{
	int				y;
	double			step;
	double			texPos;
	int				texY;
	unsigned int	color;

	y = map->ray->drawstart;
	step = 1.0 * 64 / map->ray->line_height;
	texPos = (map->ray->drawstart - WIN_Y / 2 + map->ray->line_height / 2)
		* step;
	while (y < map->ray->drawend)
	{
		// cant be 64 needs to be the difference depending on how far you-re
		texY = (int)texPos & (64-1);
		texPos += step;
		color = ft_get_pixel_color(texture, x, texY);
		ft_pixel_drawing(map->mlx, x, y, color);
		y++;
	}
}

void	draw_wall_colors(t_map *map, int x, int color)
{
	int	y;

	y = map->ray->drawstart;
	while (y < map->ray->drawend)
	{
		ft_pixel_drawing(map->mlx, x, y, color);
		y++;
	}
}

void	draw_walls(t_map *map, int x)
{
	// side = 1 vertical WALLS
	// stepY think of it was TAN
	if (map->ray->side == 1)
	{
		if (map->ray->stepy > 0)
			draw_wall_textures(map, map->texture->south, x);
		else
			draw_wall_textures(map, map->texture->north, x);
	}
	else if (map->ray->side == 0)
	{
		if (map->ray->rayDirX < 0 && map->ray->stepx < 0)
			draw_wall_textures(map, map->texture->east, x);
		else
			draw_wall_textures(map, map->texture->west, x);
	}
}

void    draw_roof_floor(t_map *map, int x)
{
	int	y;

	y = 0;
	while (y < (int)WIN_Y)
	{
		if (y <= map->ray->drawstart)
			ft_pixel_drawing(map->mlx, x, y, map->texture->roof);
		else if (y >= map->ray->drawend)
			ft_pixel_drawing(map->mlx, x, y, map->texture->floor);
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
	mlx_put_image_to_window(map->mlx->mlx_ptr, map->mlx->win_ptr,
		map->mlx->img_to_window, 0, 0);
}