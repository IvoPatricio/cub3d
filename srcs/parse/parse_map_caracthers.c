/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_caracthers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:36:50 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/18 23:29:24 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief parse_map_chars_utils: Checks if the matrix of the map 
 * contains any invalid caracthers (or not allowed)
 * @result else if there's an error everything on the heap will be 
 * freed and the program terminates with an error
*/
int	parse_map_chars_utils(t_data *data, int x, int y, int c)
{
	if (data->map[y][x] != '\n' && data->map[y][x] != FLOOR
		&& data->map[y][x] != WALL && data->map[y][x] != SPACE
		&& data->map[y][x] != NORTH && data->map[y][x] != SOUTH
		&& data->map[y][x] != EAST && data->map[y][x] != WEST)
		printf_error(data, "Map Contains Caracthers Not Allowed");
	if (data->map[y][x] == NORTH || data->map[y][x] == SOUTH
		|| data->map[y][x] == EAST || data->map[y][x] == WEST)
	{
		if (data->map[y][x] == NORTH)
			data->direction = NORTH;
		else if (data->map[y][x] == WEST)
			data->direction = WEST;
		else if (data->map[y][x] == EAST)
			data->direction = EAST;
		else if ((data->map[y][x] == SOUTH))
			data->direction = SOUTH;
		data->player_x = x;
		data->player_y = y;
		c++;
	}
	return (c);
}

/**
 * @brief parse_map_caracthers: Checks if the matrix of the map only 
 * one player
 * @result else if there's an error everything on the heap will be 
 * freed and the program terminates with an error
*/
void	parse_map_caracthers(t_data *data)
{
	int	x;
	int	y;
	int	c;

	c = 0;
	x = 0;
	y = 0;
	while (y < data->arr)
	{
		while (data->map[y][x])
		{
			c = parse_map_chars_utils(data, x, y, c);
			x++;
		}
		x = 0;
		y++;
	}
	if (c != 1)
		printf_error(data, "Map Must Have Only 1 Player");
}

/**
 * @brief map_creation: Allocates memory for the Array, and 
 * afterwards it gives the real address of each string inside argv
*/
void	map_creation(t_data *data, int i)
{
	int	x;

	x = i;
	data->arr = 0;
	while (data->argv[x])
		x++;
	data->arr = x - i;
	data->map = (char **)malloc(sizeof(char *) * (data->arr + 1));
	x = 0;
	while (data->argv[i])
	{
		data->map[x] = data->argv[i];
		x++;
		i++;
	}
	data->map[data->arr] = '\0';
}
