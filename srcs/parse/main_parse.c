#include "../../includes/cub3d.h"

void arg_parse(t_data *data)
{
	int	x;
	int	fd;

	fd = open(data->argv[1], O_RDONLY);
	if (fd == -1)
		printf_error(data, "Invalid File map");
	x = ft_strlen(data->argv[1]);
	if ((data->argv[1][x -1] != 'b') || (data->argv[1][x - 2] != 'u') || \
		(data->argv[1][x - 3] != 'c') || (data->argv[1][x - 4] != '.'))
		printf_error(data, "The map must be .cub");
	close(fd);
}

void map_array_strings(t_data *data)
{
	char	*b;
	int		fd;
	int		y;
	int		i;
	int		x;

	fd = open(data->argv[1], O_RDONLY);
	i = 0;
	while (i < 8)
	{
		b = get_next_line(fd);
		if (b)
			free(b);
		i++;
	}
	b = get_next_line(fd);
	y = 0;
	while (b)
	{
		x = 0;
		i = ft_strlen(b);
		data->map[y] = (char *)malloc(sizeof(char) * (i + 1));
		string_malloc_error(data, data->map[y]);
		while (b[x])
		{
			data->map[y][x] = b[x];
			x++;
		}
		data->map[y][x] = '\0';
		y++;
		free(b);
		b = get_next_line(fd);
	}
	data->map[y] = NULL;
	close (fd);
}

void map_array(t_data *data)
{
	char	*b;
	int		fd;
	int		i;

	i = 0;
	fd = open(data->argv[1], O_RDONLY);
	while (i < 8)
	{
		b = get_next_line(fd);
		if (b)
		{
			rgb_path_parse1(data, b, i);
			free(b);
		}
		i++;
	}
	rgb_path_parse2(data);
	b = get_next_line(fd);
	while (b)
	{
		if (b)
		{
			free(b);
			b = get_next_line(fd);
		}
		data->arr++;
	}
	data->map = (char **)malloc(sizeof(char *) * (data->arr + 1));
	array_malloc_error(data, data->map);
	close (fd);
}

void map_check_char(t_data *data)
{
	int	x;
	int	y;
	int	c;

	c = 0;
	x = 0;
	y = 0;
	while (y < data->arr)
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] != '\n' && data->map[y][x] != FLOOR \
				&& data->map[y][x] != WALL && data->map[y][x] != SPACE \
					&& data->map[y][x] != NORTH && data->map[y][x] != SOUTH \
						&& data->map[y][x] != EAST && data->map[y][x] != WEST)
				printf_error(data, "Map Contains Caracthers Not Allowed");
			if (data->map[y][x] == NORTH || data->map[y][x] == SOUTH || \
				data->map[y][x] == EAST || data->map[y][x] == WEST)
			{
				if (data->map[y][x] == NORTH)
					data->direction = NORTH;
				else if (data->map[y][x] == WEST)
					data->direction = WEST;
				else if (data->map[y][x] == EAST)
					data->direction = EAST;
				else if ((data->map[y][x] == SOUTH))
					data->direction = SOUTH;
				data->player_x = x;
				data->player_y = y;
				c++;
			}
			x++;
		}
		x = 0;
		y++;
	}
	if (c != 1)
		printf_error(data, "Map Must Have Only 1 Player");
}

void map_boundaries(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 1;
	while (data->map[0][x])
	{
		while (data->map[0][x] == WALL || data->map[0][x] == SPACE)
			x++;
		if (data->map[0][x] == '\n')
			x++;
		else
			printf_error(data, "Map Must Be Closed By Walls");
	}
	x = 0;
	while (data->map[data->arr - 1][x])
	{
		while (data->map[data->arr - 1][x] == WALL || \
			data->map[data->arr - 1][x] == SPACE)
			x++;
		if (data->map[0][x] == '\n')
			x++;
		else
			printf_error(data, "Map Must Be Closed By Walls");
	}
	x = 0;
	while (y < data->arr - 2)
	{
		while (data->map[y][x] == SPACE)
			x++;
		x = 0;
	}

}

void main_parse(t_data *data)
{
	data->arr = 0;
	arg_parse(data);
	map_array(data);
	map_array_strings(data);
	map_check_char(data);

	//map_boundaries(data); Usless function, map isnt being parsed correctly for closed map while considering the spaces
	printf_map(data);
}