#include "../../includes/cub3d.h"

void	arg_parse(t_data *data)
{
	int	x;
	int	fd;

	fd = open(data->argv[1], O_RDONLY);
	if (fd == -1)
		printf_error(data, "Invalid File map");
	x = ft_strlen(data->argv[1]);
	if ((data->argv[1][x - 1] != 'b') || (data->argv[1][x - 2] != 'u')
		|| (data->argv[1][x - 3] != 'c') || (data->argv[1][x - 4] != '.'))
		printf_error(data, "The map must be .cub");
	close(fd);
}

void	map_check_char(t_data *data)
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
			if (data->map[y][x] != '\n' && data->map[y][x] != FLOOR
				&& data->map[y][x] != WALL && data->map[y][x] != SPACE
				&& data->map[y][x] != NORTH && data->map[y][x] != SOUTH
				&& data->map[y][x] != EAST && data->map[y][x] != WEST)
				printf_error(data, "Map Contains Caracthers Not Allowed");
			if (data->map[y][x] == NORTH || data->map[y][x] == SOUTH
				|| data->map[y][x] == EAST || data->map[y][x] == WEST)
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

void	map_flood_fill(t_data *data)
{
	int		x;
	int		y;
	int		i;
	char	c;

	int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
	int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
	x = 0;
	y = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0' || data->map[y][x] == data->direction)
			{
				i = 0;
				while (i < 8)
				{
					if ((y + dy[i]) >= data->arr)
						printf_error(data, "Map Must Be Closed By Walls");
					c = data->map[y + dy[i]][x + dx[i]];
					if (c != '1' && c != '0' && c != data->direction)
						printf_error(data, "Map Must Be Closed By Walls");
					i++;
				}
			}
			x++;
		}
		y++;
		x = 0;
	}
}

void file_read(t_data *data, int fd, int index)
{
	char *line;

	line = get_next_line(fd);
	if (line)
		file_read(data, fd, index + 1);
	else
		data->argv = (char **)malloc(sizeof(char *) * (index + 1));
	if (data->argv)
		data->argv[index] = line;
}

void file_array(t_data *data)
{
	char	*b;
	int		fd;
	int		i;


	fd = open(data->argv[1], O_RDONLY);
	if (fd != -1)
		file_read(data, fd, 0);
	i = 0;
	close(fd);
}

char *ft_argv_str(t_data *data, char *str, int ind, int i)
{
	int	x;

	x = 0;
	while (data->argv[ind][i])
	{
		if (isspace(data->argv[ind][i]) != 0)
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

char *ft_argv_new(t_data *data, int ind)
{
	char *str;
	int	i = 2;
	int	x = 0;

	while (data->argv[ind][i])
	{
		if (isspace(data->argv[ind][i]) != 0)
			i++;
		else
		{
			x++;
			i++;
		}
	}
	i = 2;
	str = (char *)malloc(sizeof(char) * (x + 1));
	return (ft_argv_str(data, str, ind, i));
}

void main_parse(t_data *data)
{
	data->arr = 0;
	arg_parse(data);
	file_array(data);
	int fd;
	int i = 0;
	while (data->argv[i])
	{
		if (strncmp(data->argv[i], "NO ", 2) == 0)
			data->no = ft_argv_new(data, i);
		else if (strncmp(data->argv[i], "SO ", 2) == 0)
			data->so = ft_argv_new(data, i);
		else if (strncmp(data->argv[i], "WE ", 2) == 0)
			data->we = ft_argv_new(data, i);
		else if (strncmp(data->argv[i], "EA ", 2) == 0)
			data->ea = ft_argv_new(data, i);
		else if (strncmp(data->argv[i], "F ", 2) == 0)
			data->f = ft_argv_new(data, i);
		else if (strncmp(data->argv[i], "C ", 2) == 0)
			data->c = ft_argv_new(data, i);
		i++;
	}
	/*
	fd = open(data->no, O_RDONLY);
	if (fd == -1)
		printf("PATH DOESNT EXIST%s\n", data->no);*/

	printf("data->f%s\n", data->no);
	printf("data->f%s\n", data->so);
	printf("data->f%s\n", data->we);
	printf("data->f%s\n", data->ea);
	printf("data->f%s\n", data->f);
	printf("data->f%s\n", data->c);
	//map_array_strings(data);
	// map_check_char(data);
	// map_flood_fill(data);
	// printf_map(data);
}