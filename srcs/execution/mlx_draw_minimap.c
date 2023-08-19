/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 06:53:07 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/19 07:03:30 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief draw_minimap_colors: draws a minimap, right now its drawing
 * a 1:1 minimap (aspect ratio), its easy to implement aspect ratio 
 * depending on the resolution just looks uglier(opnion)
 * since everything else in this project is constant
 * some games like GTA_SA the minimap is always 4:3
*/
void	draw_minimap_colors(t_map *map, int x, int y, int color)
{
	int	x_b;
	int	y_b;

	x_b = 0;
	y_b = 0;
	x = x * (WIN_X / 30);
	y = y * (WIN_X / 30);
	while (y_b < (WIN_X / 30))
	{
		while (x_b < (WIN_X / 30))
		{
			ft_pixel_drawing(map->mlx, (x + x_b), (y + y_b), color);
			x_b++;
		}
		x_b = 0;
		y_b++;
	}
}

/**
 * @brief Function that will check when Its a wall or floor and draw
 * the player
*/
void	minimap(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->map[y])
	{
		while (map->map[y][x])
		{
			if (map->map[y][x] == WALL)
				draw_minimap_colors(map, x, y, 0x000000);
			else if (map->map[y][x] == FLOOR)
				draw_minimap_colors(map, x, y, 0x0000FF);
			x++;
		}
		x = 0;
		y++;
	}
	draw_minimap_colors(map, (int)map->play->pos_x, \
		(int)map->play->pos_y, 0xFF0000);
}