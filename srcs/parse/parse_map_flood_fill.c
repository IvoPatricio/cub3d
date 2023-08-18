/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_flood_fill.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:02:21 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/18 02:16:10 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief map_vector_dx: Sadly 42 doesnt allow dx[3] = {1,0,-1}. This function
 * allocates each X position like a vector when combined with Y
 * @result returns DX with vector like values
*/
int	*map_vector_dx(void)
{
	int	*dx;

	dx = (int *)malloc(sizeof(int) * (9));
	dx[0] = 0;
	dx[1] = 1;
	dx[2] = -1;
	dx[3] = 0;
	dx[4] = 1;
	dx[5] = -1;
	dx[6] = -1;
	dx[7] = 1;
	dx[8] = '\0';
	return (dx);
}

/**
 * @brief map_vector_dy: Sadly 42 doesnt allow dy[3] = {1,0,-1}. This function
 * allocates each Y position like a vector when combined with X
 * @result returns DY with vector like values
*/
int	*map_vector_dy(void)
{
	int	*dy;

	dy = (int *)malloc(sizeof(int) * (9));
	dy[0] = -1;
	dy[1] = -1;
	dy[2] = -1;
	dy[3] = 1;
	dy[4] = 1;
	dy[5] = 1;
	dy[6] = 0;
	dy[7] = 0;
	dy[8] = '\0';
	return (dy);
}

/**
 * @brief map_closed_by_walls: Check if the map is closed by walls using "vectors"
 * making sure the player position or the floors positions is always surrounded
 * by walls, freeing the "vectors" when the function finishs
*/
void	map_closed_by_walls(t_data *data, int x, int y)
{
	char	c;
	int		i;
	int		*dx;
	int		*dy;

	i = 0;
	dx = map_vector_dx();
	dy = map_vector_dy();
	while (i < 8)
	{
		if ((y + dy[i]) >= data->arr)
			printf_error(data, "Map Must Be Closed By Walls");
		c = data->map[y + dy[i]][x + dx[i]];
		if (c != '1' && c != '0' && c != data->direction)
			printf_error(data, "Map Must Be Closed By Walls");
		i++;
	}
	free(dx);
	free(dy);
}

/**
 * @brief map_flood_fill: Checks if the map is closed by walls using the player
 * or floor position
*/
void	map_flood_fill(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0' || data->map[y][x] == data->direction)
				map_closed_by_walls(data, x, y);
			x++;
		}
		y++;
		x = 0;
	}
}
