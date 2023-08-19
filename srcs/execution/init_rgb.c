/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:43:12 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/19 07:08:20 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief create_trgb: converts 4 different integers into a single
 * integer for the RGB value 
 * @result returning the value of the 4 integers in a single one
*/
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * @brief map_rgb: send an array of integers(using atoi) to create 
 * the final RGB value of a single integer using 4 ints
 * T = Transparency R = Red G = Green B = Blue
*/
void	map_rgb(t_data *data, t_texture *texture)
{
	texture->floor = create_trgb(0, ft_atoi(data->f_arr[0]), \
		ft_atoi(data->f_arr[1]), ft_atoi(data->f_arr[2]));
	texture->roof = create_trgb(0, ft_atoi(data->f_arr[0]), \
		ft_atoi(data->c_arr[1]), ft_atoi(data->c_arr[2]));
}
