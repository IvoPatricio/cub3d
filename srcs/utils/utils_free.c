/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:39:44 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 23:41:55 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(t_data *data)
{
	int	i;

	if (data->argv)
	{
		i = 0;
		while (data->argv[i])
		{
			free(data->argv[i]);
			i++;
		}
		free(data->argv);
	}
	if (data->map)
		free(data->map);
	free_rest_map(data);
}

void	free_rest_map(t_data *data)
{
	int	i;

	if (data->f_arr)
	{
		i = 0;
		while (data->f_arr[i])
		{
			free(data->f_arr[i]);
			i++;
		}
		free(data->f_arr);
	}
	if (data->c_arr)
	{
		i = 0;
		while (data->c_arr[i])
		{
			free(data->c_arr[i]);
			i++;
		}
		free(data->c_arr);
	}
	if (data)
		free(data);
}

void	free_structs_mlx(t_map *map)
{
	free_map(map->data);
	if (map->ray)
		free(map->ray);
	if (map->play)
		free(map->play);
	if (map->texture)
		free(map->texture);
	if (map->mlx)
		free(map->mlx);
	exit(0);
}
