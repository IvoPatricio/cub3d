/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:36:57 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/18 02:23:00 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief paths_parse_caracthers: Checks if the array of strings has a non integer value
 * @result if there's an non integer everything on the heap will be freed and the program
 * terminates with an error
*/
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

/**
 * @brief paths_creation_parse: Separates the values of RGB in an Array of strings
 * and afterwards it checks if the RGB value is between 0-255
 * @result else if there's an error everything on the heap will be freed and the program
 * terminates with an error
*/
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

/**
 * @brief path_utils: if open returns -1 it means the path doesnt exist
 * @result if path_utils returns -1 check_if_path_valid will terminate the program with
 * an error else it will keep executing till it finds an error or it is manually terminated
*/
int	path_utils(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

/**
 * @brief check_if_path_valid: Checks if the paths inside the string are valid
 * @result else if there's an error everything on the heap will be freed and the program
 * terminates with an error
*/
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
