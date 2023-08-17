/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_lodev_dda.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:11:29 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 23:46:23 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	raycast_dda(t_map *map)
{
	t_ray	*ray;

	ray = map->ray;
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepy;
			ray->side = 1;
		}
		if (map->map[ray->mapY][ray->mapX] == WALL)
			ray->hit = 1;
	}
	if (ray->side == 0)
	{
		ray->walldist = ray->sideDistX - ray->deltaDistX;
	}
	else
		ray->walldist = ray->sideDistY - ray->deltaDistY;
	ray->line_height = (int)(WIN_Y / ray->walldist);
	ray->drawstart = -ray->line_height / 2 + (int)WIN_Y / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->line_height / 2 + (int)WIN_Y / 2;
	if (ray->drawend >= (int)WIN_Y)
		ray->drawend = (int)WIN_Y - 1;
	if (ray->side == 0)
		ray->wallhit = map->play->pos_y + ray->walldist * ray->rayDirY;
	else
		ray->wallhit = map->play->pos_x + ray->walldist * ray->rayDirX;
	ray->wallhit -= floor(ray->wallhit);
}

void	raycast_2(t_map *map)
{
	t_ray	*ray;

	ray = map->ray;
	if (ray->rayDirX < 0)
	{
		ray->stepx = -1;
		ray->sideDistX = (map->play->pos_x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepx = 1;
		ray->sideDistX = (ray->mapX + 1.0 - map->play->pos_x) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepy = -1;
		ray->sideDistY = (map->play->pos_y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepy = 1;
		ray->sideDistY = (ray->mapY + 1.0 - map->play->pos_y) * ray->deltaDistY;
	}
	raycast_dda(map);
}

void	raycast_1(t_map *map, int i)
{
	t_ray	*ray;

	ray = map->ray;
	ray->cameraX = 2 * i / (double)WIN_X - 1;
	ray->rayDirX = map->play->dir_x + map->play->plane_x * ray->cameraX;
	ray->rayDirY = map->play->dir_y + map->play->plane_y * ray->cameraX;
	ray->mapX = (int)map->play->pos_x;
	ray->mapY = (int)map->play->pos_y;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	raycast_2(map);
}
