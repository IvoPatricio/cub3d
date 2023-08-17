#include "../../includes/cub3d.h"

/*
 * @brief function who returns the size of a string
 * @param str ptr on char
 * @return integer that defines lenght str
int ft_strlen(char *str)
{
	int i =0;
	while (str[i])
		i++;
	return i;
}*/

void	arg_parse(t_data *data)
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

char *ft_isspace_file2(t_data *data, char *str, int ind, int i)
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

char *ft_isspace_file1(t_data *data, int ind, int z)
{
	char *str;
	int	i;
	int	x;

	i = 0 + z;
	x = 0;
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
	i = 0 + z;
	str = (char *)malloc(sizeof(char) * (x + 1));
	return (ft_isspace_file2(data, str, ind, i));
}

char *ft_utils_add_values_data(t_data *data, int i, int value)
{
	data->map_time++;
	return (ft_isspace_file1(data, i, value));
}

void ft_add_values_map(t_data *data, int i)
{
	int	x;

	x = i;
	data->arr = 0;
	while (data->argv[x])
		x++;
	data->arr = x - i;
	data->map = (char **)malloc(sizeof(char *) * (data->arr + 1));
	x = 0;
	while (data->argv[i])
	{
		data->map[x] = data->argv[i];
		x++;
		i++;
	}
	data->map[data->arr] = '\0';
}

void ft_add_values_data(t_data *data)
{
	int i;

	i = 0;
	data->map_time = 0;
	while (data->argv[i] && data->map_time < 6)
	{
		ft_isspace_file1(data, i, 0);
		if (strncmp(data->argv[i], "NO./", 4) == 0)
			data->no = ft_utils_add_values_data(data, i, 2);
		else if (strncmp(data->argv[i], "SO./", 4) == 0)
			data->so = ft_utils_add_values_data(data, i, 2);
		else if (strncmp(data->argv[i], "WE./", 4) == 0)
			data->we = ft_utils_add_values_data(data, i, 2);
		else if (strncmp(data->argv[i], "EA./", 4) == 0)
			data->ea = ft_utils_add_values_data(data, i, 2);
		else if (strncmp(data->argv[i], "F", 1) == 0)
			data->f = ft_utils_add_values_data(data, i, 1);
		else if (strncmp(data->argv[i], "C", 1) == 0)
			data->c = ft_utils_add_values_data(data, i, 1);
		i++;
	}
	ft_add_values_map(data, i);
	if (data->map_time < 6)
		printf_error(data, "Invalid File Variables");
}

int ft_path_utils(char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return -1;
	close(fd);
	return 0;
}

void ft_check_path(t_data *data)
{
	if (ft_path_utils(data->no) == -1)
		printf_error(data, "Invalid North Path");
	if (ft_path_utils(data->so) == -1)
		printf_error(data, "Invalid South Path");
	if (ft_path_utils(data->we) == -1)
		printf_error(data, "Invalid West Path");
	if (ft_path_utils(data->ea) == -1)
		printf_error(data, "Invalid East Path");
}

void	rgb_path_parse3(t_data *data)
{
	int		i;
	int		x;

	data->f_arr = ft_split(data->f, ',');
	data->c_arr = ft_split(data->c, ',');
	i = 0;
	x = 0;
	while (i < 3)
	{
		while (data->c_arr[i][x])
		{
			if (isdigit(data->c_arr[i][x]))
				x++;
			else
				printf_error(data, "Invalid Roof NonInteger Caracthers");
		}
		x = 0;
		while (data->f_arr[i][x])
		{
			if (isdigit(data->f_arr[i][x]))
				x++;
			else
				printf_error(data, "Invalid Floor NonInteger Caracthers");
		}
		x = 0;
		if (ft_atoi(data->f_arr[i]) > 255 || ft_atoi(data->f_arr[i]) < 0)
			printf_error(data, "Invalid RGB value 0-255");
		if (ft_atoi(data->c_arr[i]) > 255 || ft_atoi(data->c_arr[i]) < 0)
			printf_error(data, "Invalid RGB value 0-255");
		i++;
	}
}

void main_parse(t_data *data)
{
	arg_parse(data);
	file_array(data);
	ft_add_values_data(data);
	ft_check_path(data);
	map_check_char(data);
	map_flood_fill(data);
	rgb_path_parse3(data);
	printf_paths(data);
	printf_map(data);
}