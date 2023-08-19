/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:29:24 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/19 07:28:02 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief init_player1: Sets different values on the struct player
 * depending on the starter direction
*/
void	init_player1(t_data *data, t_play *play)
{
	play->pos_x = data->player_x + 0.5;
	play->pos_y = data->player_y + 0.5;
	if (data->direction == NORTH)
	{
		play->dir_x = 0;
		play->dir_y = -1;
		play->plane_x = 0.66;
		play->plane_y = 0;
	}
	else if (data->direction == SOUTH)
	{
		play->dir_x = 0;
		play->dir_y = 1;
		play->plane_x = -0.66;
		play->plane_y = 0;
	}
	init_player_rest(data, play);
}

/**
 * @brief init_player_rest: Sets different values on the struct player
 * depending on the starter direction
*/
void	init_player_rest(t_data *data, t_play *play)
{
	if (data->direction == EAST)
	{
		play->dir_x = -1;
		play->dir_y = 0;
		play->plane_x = 0;
		play->plane_y = 0.66;
	}
	else if (data->direction == WEST)
	{
		play->dir_x = 1;
		play->dir_y = 0;
		play->plane_x = 0;
		play->plane_y = -0.66;
	}
}

/**
 * @brief init_textured: saves the values of the variables
 * to the struct texture, even tho it wasnt needed :laugh:
 * just easier for the printf structs
*/
void	init_textured(t_data *data, t_texture *texture)
{
	texture->n = data->no;
	texture->s = data->so;
	texture->w = data->we;
	texture->e = data->ea;
	if (data->direction == NORTH)
		texture->player_direction = NORTH;
	else if (data->direction == SOUTH)
		texture->player_direction = SOUTH;
	else if (data->direction == EAST)
		texture->player_direction = EAST;
	else if ((data->direction == WEST))
		texture->player_direction = WEST;
	map_rgb(data, texture);
}

/**
 * @brief init_structs: allocates memory for the structs needed for the
 * raycasting, mlx, player and textures so everything can be accessible 
 * using a single struct MAP, and sets the old position of the player
 * block to a floor
*/
void	init_structs(t_map *map)
{
	map->texture = malloc(sizeof(t_texture));
	struct_malloc_error(map, map->texture, sizeof(map->texture));
	map->play = malloc(sizeof(t_play));
	struct_malloc_error(map, map->play, sizeof(map->play));
	map->ray = malloc(sizeof(t_ray));
	struct_malloc_error(map, map->ray, sizeof(map->ray));
	map->mlx = malloc(sizeof(t_mlx));
	struct_malloc_error(map, map->mlx, sizeof(map->mlx));
	map->map = map->data->map;
	map->map[map->data->player_y][map->data->player_x] = FLOOR;
	init_textured(map->data, map->texture);
	init_player1(map->data, map->play);
}
