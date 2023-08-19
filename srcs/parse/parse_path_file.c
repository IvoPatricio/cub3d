/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:37:03 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/18 23:32:45 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief path_creation: Increments map_time because there can only 
 * be 4 paths + 2 RGB
 * @return returns the new modified string
*/
char	*path_creation(t_data *data, int i, int value)
{
	data->map_time++;
	return (isspace_file1(data, i, value));
}

/**
 * @brief isspace_file2: Creates an allocation while taking in 
 * consideration how many spaces/tabs the string had previously and 
 * remove the first 4 letters if N/S/W/E or the first letter if floor/celling
 * @return returns the new modified string
*/
char	*isspace_file2(t_data *data, char *str, int ind, int i)
{
	int	x;

	x = 0;
	while (data->argv[ind][i])
	{
		if (ft_isspace(data->argv[ind][i]) != 0)
			i++;
		else
		{
			str[x] = data->argv[ind][i];
			x++;
			i++;
		}
	}
	str[x] = '\0';
	free(data->argv[ind]);
	data->argv[ind] = (char *)malloc(sizeof(char) * (x + 1));
	x = -1;
	while (str[++x])
		data->argv[ind][x] = str[x];
	data->argv[ind][x] = '\0';
	free(str);
	return (data->argv[ind]);
}

/**
 * @brief isspace_file1: Counts all the spaces from the string, works 
 * as an isspace for strings
 * @return returns the new modified string
*/
char	*isspace_file1(t_data *data, int ind, int z)
{
	char	*str;
	int		i;
	int		x;

	i = 0 + z;
	x = 0;
	while (data->argv[ind][i])
	{
		if (ft_isspace(data->argv[ind][i]) != 0)
			i++;
		else
		{
			x++;
			i++;
		}
	}
	i = 0 + z;
	str = (char *)malloc(sizeof(char) * (x + 1));
	return (isspace_file2(data, str, ind, i));
}

/**
 * @brief parse_path: Removes spaces/tabs/newlines from an array of 
 * strings till it parsed all different paths and compares the first 
 * letters necessary for the creation of the paths or there wont be one
 * @return the position I(Y) in the Array
*/
int	parse_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->argv[i] && data->map_time < 6)
	{
		isspace_file1(data, i, 0);
		if (ft_strncmp(data->argv[i], "NO./", 4) == 0)
			data->no = path_creation(data, i, 2);
		else if (ft_strncmp(data->argv[i], "SO./", 4) == 0)
			data->so = path_creation(data, i, 2);
		else if (ft_strncmp(data->argv[i], "WE./", 4) == 0)
			data->we = path_creation(data, i, 2);
		else if (ft_strncmp(data->argv[i], "EA./", 4) == 0)
			data->ea = path_creation(data, i, 2);
		else if (ft_strncmp(data->argv[i], "F", 1) == 0)
			data->f = path_creation(data, i, 1);
		else if (ft_strncmp(data->argv[i], "C", 1) == 0)
			data->c = path_creation(data, i, 1);
		i++;
	}
	if (data->map_time < 6)
		printf_error(data, "Invalid File Paths Variables");
	check_if_path_valid(data);
	paths_creation_parse(data);
	return (i);
}
