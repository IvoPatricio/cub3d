/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:11:37 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/19 05:57:16 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_key_w(t_map *map, int key_code)
{
	double	tempx;
	double	tempy;

	tempx = map->play->pos_x;
	tempy = map->play->pos_y;
	if (key_code == W_KEY)
	{
		if (map->map[(int)map->play->pos_y][((int)map->play->pos_x \
				+ (int)map->play->dir_x * (int)PLAYER_SPEED)] == FLOOR)
			map->play->pos_x += map->play->dir_x * PLAYER_SPEED;
		if (map->map[(int)map->play->pos_y][((int)map->play->pos_x \
				+ (int)map->play->dir_x * (int)PLAYER_SPEED)] == WALL)
			map->play->pos_x = tempx;
		if (map->map[(int)(map->play->pos_y + (int)map->play->dir_y \
				* (int)PLAYER_SPEED)][(int)map->play->pos_x] == FLOOR)
			map->play->pos_y += map->play->dir_y * PLAYER_SPEED;
		if (map->map[(int)(map->play->pos_y + (int)map->play->dir_y \
				* (int)PLAYER_SPEED)][(int)map->play->pos_x] == WALL)
			map->play->pos_y = tempy;
	}
}

void	ft_key_s(t_map *map, int key_code)
{
	double	tempx;
	double	tempy;

	tempx = map->play->pos_x;
	tempy = map->play->pos_y;
	if (key_code == S_KEY)
	{
		if (map->map[(int)map->play->pos_y][((int)map->play->pos_x \
				- (int)map->play->dir_x * (int)PLAYER_SPEED)] == FLOOR)
			map->play->pos_x -= map->play->dir_x * PLAYER_SPEED;
		if (map->map[(int)map->play->pos_y][((int)map->play->pos_x \
				- (int)map->play->dir_x * (int)PLAYER_SPEED)] == WALL)
			map->play->pos_x = tempx;
		if (map->map[((int)map->play->pos_y - (int)map->play->dir_y \
				* (int)PLAYER_SPEED)][(int)map->play->pos_x] == FLOOR)
			map->play->pos_y -= map->play->dir_y * PLAYER_SPEED;
		if (map->map[((int)map->play->pos_y - (int)map->play->dir_y \
				* (int)PLAYER_SPEED)][(int)map->play->pos_x] == WALL)
			map->play->pos_y = tempy;
	}
}

void	ft_key_a(t_map *map, int key_code)
{
	double	tempx;
	double	tempy;

	tempx = map->play->pos_x;
	tempy = map->play->pos_y;
	if (key_code == A_KEY)
	{
		if ((map->map[(int)map->play->pos_y][((int)map->play->pos_x \
					- (int)map->play->plane_x * (int)PLAYER_SPEED)]) == FLOOR)
			map->play->pos_x -= map->play->plane_x * PLAYER_SPEED;
		if ((map->map[(int)map->play->pos_y][((int)map->play->pos_x \
					- (int)map->play->plane_x * (int)PLAYER_SPEED)]) == WALL)
			map->play->pos_x = tempx;
		if (map->map[((int)map->play->pos_y - (int)map->play->plane_y \
				* (int)PLAYER_SPEED)][(int)map->play->pos_x] == FLOOR)
			map->play->pos_y -= map->play->plane_y * PLAYER_SPEED;
		if (map->map[((int)map->play->pos_y - (int)map->play->plane_y \
				* (int)PLAYER_SPEED)][(int)map->play->pos_x] == WALL)
			map->play->pos_y = tempy;
	}
}

void	ft_key_d(t_map *map, int key_code)
{
	double	tempx;
	double	tempy;

	tempx = map->play->pos_x;
	tempy = map->play->pos_y;
	if (key_code == D_KEY)
	{
		if ((map->map[(int)map->play->pos_y][((int)map->play->pos_x \
					+ (int)map->play->plane_x * (int)PLAYER_SPEED)]) == FLOOR)
			map->play->pos_x += map->play->plane_x * PLAYER_SPEED;
		if ((map->map[(int)map->play->pos_y][((int)map->play->pos_x \
					+ (int)map->play->plane_x * (int)PLAYER_SPEED)]) == WALL)
			map->play->pos_x = tempx;
		if (map->map[((int)map->play->pos_y + (int)map->play->plane_y \
				* (int)PLAYER_SPEED)][(int)map->play->pos_x] == FLOOR)
			map->play->pos_y += map->play->plane_y * PLAYER_SPEED;
		if (map->map[((int)map->play->pos_y + (int)map->play->plane_y \
				* (int)PLAYER_SPEED)][(int)map->play->pos_x] == WALL)
			map->play->pos_y = tempy;
	}
}

/**
 * @brief ft_keys: Depending on the keycode it will do an action
*/
int	ft_keys(int key_code, t_map *map)
{
	if (key_code == CLOSE)
		ft_destroyer(map);
	if (key_code == W_KEY)
		ft_key_w(map, key_code);
	if (key_code == S_KEY)
		ft_key_s(map, key_code);
	if (key_code == A_KEY)
		ft_key_a(map, key_code);
	if (key_code == D_KEY)
		ft_key_d(map, key_code);
	if (key_code == RIGHT && (map->data->direction == WEST
			|| map->data->direction == EAST))
		ft_key_angle(map, -(double)ROTATE_SPEED);
	else if (key_code == RIGHT)
		ft_key_angle(map, (double)ROTATE_SPEED);
	if (key_code == LEFT && (map->data->direction == WEST
			|| map->data->direction == EAST))
		ft_key_angle(map, (double)ROTATE_SPEED);
	else if (key_code == LEFT)
		ft_key_angle(map, -(double)ROTATE_SPEED);
	raydrawing(map);
	return (0);
}
