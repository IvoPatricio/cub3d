/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:21:20 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 23:21:22 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_pixel_drawing(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->buffer + (y * mlx->b + x * (mlx->a / 8));
	*(unsigned int *)dst = color;
}

unsigned int	ft_get_pixel_color(t_mlx *mlx, int x, int y)
{
	int	*dst;
	int	color;

	dst = (void *)mlx->buffer + (y * mlx->b + x * (mlx->a / 8));
	color = *(int *)dst;
	return (color);
}