/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:36:44 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/17 18:42:59 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	file_name_parse(t_data *data)
{
	int	x;
	int	fd;

	fd = open(data->argv[1], O_RDONLY);
	if (fd == -1)
	{
		data->argv = NULL;
		printf_error(data, "Invalid File map");
	}
	x = ft_strlen(data->argv[1]);
	if ((data->argv[1][x - 1] != 'b') || (data->argv[1][x - 2] != 'u')
		|| (data->argv[1][x - 3] != 'c') || (data->argv[1][x - 4] != '.'))
	{
		data->argv = NULL;
		printf_error(data, "The map must be .cub");
	}
	close(fd);
}

void	reading_file(t_data *data, int fd, int index)
{
	char	*line;

	line = get_next_line(fd);
	if (line)
		reading_file(data, fd, index + 1);
	else
		data->argv = (char **)malloc(sizeof(char *) * (index + 1));
	if (data->argv)
		data->argv[index] = line;
}

void	file_array(t_data *data)
{
	char	*b;
	int		fd;
	int		i;

	fd = open(data->argv[1], O_RDONLY);
	if (fd != -1)
		reading_file(data, fd, 0);
	i = 0;
	close(fd);
}
