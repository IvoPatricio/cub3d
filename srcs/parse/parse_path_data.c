/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:36:57 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 19:24:43 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	paths_parse_caracthers(t_data *data, int i)
{
	int	x;

	x = 0;
	while (data->c_arr[i][x])
	{
		if (ft_isdigit(data->c_arr[i][x]))
			x++;
		else
			printf_error(data, "Invalid Roof NonInteger Caracthers");
	}
	x = 0;
	while (data->f_arr[i][x])
	{
		if (ft_isdigit(data->f_arr[i][x]))
			x++;
		else
			printf_error(data, "Invalid Floor NonInteger Caracthers");
	}
}

void	paths_creation_parse(t_data *data)
{
	int	i;

	data->f_arr = ft_split(data->f, ',');
	data->c_arr = ft_split(data->c, ',');
	i = 0;
	while (i < 3)
	{
		paths_parse_caracthers(data, i);
		if (ft_atoi(data->f_arr[i]) > 255 || ft_atoi(data->f_arr[i]) < 0)
			printf_error(data, "Invalid RGB value 0-255");
		if (ft_atoi(data->c_arr[i]) > 255 || ft_atoi(data->c_arr[i]) < 0)
			printf_error(data, "Invalid RGB value 0-255");
		i++;
	}
}

int	path_utils(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

void	check_if_path_valid(t_data *data)
{
	if (path_utils(data->no) == -1)
		printf_error(data, "Invalid North Path");
	if (path_utils(data->so) == -1)
		printf_error(data, "Invalid South Path");
	if (path_utils(data->we) == -1)
		printf_error(data, "Invalid West Path");
	if (path_utils(data->ea) == -1)
		printf_error(data, "Invalid East Path");
}
