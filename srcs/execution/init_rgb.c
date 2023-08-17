/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:43:12 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 23:53:23 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	map_rgb(t_data *data, t_texture *texture)
{
	char	*arr;

	texture->floor = create_trgb(0, ft_atoi(data->f_arr[0]), \
		ft_atoi(data->f_arr[1]), ft_atoi(data->f_arr[2]));
	texture->roof = create_trgb(0, ft_atoi(data->f_arr[0]), \
		ft_atoi(data->c_arr[1]), ft_atoi(data->c_arr[2]));
}
