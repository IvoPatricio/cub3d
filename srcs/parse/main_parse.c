/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:36:38 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 19:57:16 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 * @brief function who returns the size of a string
 * @param str ptr on char
 * @return integer that defines lenght str
int	ft_strlen(char *str)
{
	int i =0;
	while (str[i])
		i++;
	return (i);
}*/
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
