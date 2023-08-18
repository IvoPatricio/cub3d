/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:39:50 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 23:42:13 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	string_malloc_error(t_data *data, char *a)
{
	if (!a)
		printf_error(data, "String Allocation Failed");
}

void	array_malloc_error(t_data *data, char **a)
{
	if (!a)
		printf_error(data, "Array Allocation Failed");
}

void	struct_malloc_error(t_map *map, const void *random, size_t size)
{
	if (!random || size <= 0)
	{
		printf("\e[1;31mERROR\n\e[0;0m");
		printf("\e[0;34m\n\e[0;0m Struct Allocation Failed");
		free_structs_mlx(map);
	}
}
