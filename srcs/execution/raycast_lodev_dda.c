/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_lodev_dda.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:11:29 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/18 00:02:37 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief raycast_rest_dda: Calculates the distance of perpendicular 
 * ray (without fisheye) and calculate height of line to draw on screen
 * wallhit = where exactly the wall was hit
*/
void	raycast_rest_dda(t_map *map)
{
	t_ray	*ray;

	ray = map->ray;
	if (ray->side == 0)
	{
		ray->walldist = ray->sidedist_x - ray->deltadist_x;
	}
	else
		ray->walldist = ray->sidedist_y - ray->deltadist_y;
	ray->line_height = (int)(WIN_Y / ray->walldist);
	ray->drawstart = -ray->line_height / 2 + (int)WIN_Y / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->line_height / 2 + (int)WIN_Y / 2;
	if (ray->drawend >= (int)WIN_Y)
		ray->drawend = (int)WIN_Y - 1;
	if (ray->side == 0)
		ray->wallhit = map->play->pos_y + ray->walldist * ray->raydir_y;
	else
		ray->wallhit = map->play->pos_x + ray->walldist * ray->raydir_x;
	ray->wallhit -= floor(ray->wallhit);
}

/**
 * @brief raycast_dda: jump to next map square, either in x-direction, 
 * or in y-direction and checks if you hit a wall
*/
void	raycast_dda(t_map *map)
{
	t_ray	*ray;

	ray = map->ray;
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->stepy;
			ray->side = 1;
		}
		if (map->map[ray->map_y][ray->map_x] == WALL)
			ray->hit = 1;
	}
	raycast_rest_dda(map);
}

/**
 * @brief raycast_2: Calculates the steps and initial sideDist
*/
void	raycast_2(t_map *map)
{
	t_ray	*ray;

	ray = map->ray;
	if (ray->raydir_x < 0)
	{
		ray->stepx = -1;
		ray->sidedist_x = (map->play->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - map->play->pos_x)
			* ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->stepy = -1;
		ray->sidedist_y = (map->play->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - map->play->pos_y)
			* ray->deltadist_y;
	}
}

/**
 * @brief raycast_1: calculates the rays position and directions
 * and x-coordinate in camera space
*/
void	raycast_1(t_map *map, int i)
{
	t_ray	*ray;

	ray = map->ray;
	ray->camera_x = 2 * i / (double)WIN_X - 1;
	ray->raydir_x = map->play->dir_x + map->play->plane_x * ray->camera_x;
	ray->raydir_y = map->play->dir_y + map->play->plane_y * ray->camera_x;
	ray->map_x = (int)map->play->pos_x;
	ray->map_y = (int)map->play->pos_y;
	if (ray->raydir_x == 0)
		ray->deltadist_x = 1e30;
	else
		ray->deltadist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->deltadist_y = 1e30;
	else
		ray->deltadist_y = fabs(1 / ray->raydir_y);
	raycast_2(map);
	raycast_dda(map);
}
