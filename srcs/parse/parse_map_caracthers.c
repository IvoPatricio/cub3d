/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_caracthers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:36:50 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 19:03:18 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
