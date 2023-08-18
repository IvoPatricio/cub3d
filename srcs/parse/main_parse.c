/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:36:38 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/18 02:23:33 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Init_data: Sets the values of struct data to NULL pointers
*/
void	init_data(t_data *data, char **argv)
{
	data->argv = argv;
	data->f_arr = NULL;
	data->c_arr = NULL;
	data->f = NULL;
	data->c = NULL;
	data->no = NULL;
	data->we = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->map = NULL;
	data->map_time = 0;
}

/**
 * @brief Main_parse: Calls other functions to parse the file, paths, rgb colours & map
 * @result If any function gives an error the program will give an error in STDERR and exit
*/
void	main_parse(t_data *data, char **argv)
{
	int	i;

	init_data(data, argv);
	file_name_parse(data);
	file_array(data);
	i = parse_path(data);
	map_creation(data, i);
	parse_map_caracthers(data);
	map_flood_fill(data);
}
