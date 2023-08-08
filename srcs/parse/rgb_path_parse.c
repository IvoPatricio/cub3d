#include "../../includes/cub3d.h"

char *give_mem_char(char *dest, char *src)
{
	int	len;
	int	i;

	len = ft_strlen(src); 
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
	{
		free(dest);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

void rgb_path_parse3(t_data *data)
{
    int		i;
	char 	*arr;

	arr = data->f_arr[0];
	arr += 2;
	if (ft_atoi(arr) > 255 || ft_atoi(arr) < 0)
		printf_error(data, "Invalid RGB value 0-255");
	arr = data->c_arr[0];
	arr += 2;
	if (ft_atoi(arr) > 255 || ft_atoi(arr) < 0)
		printf_error(data, "Invalid RGB value 0-255");
	i = 1;
	while (i < 3)
	{
		if (ft_atoi(data->f_arr[i]) > 255 || ft_atoi(data->f_arr[i]) < 0)
			printf_error(data, "Invalid RGB value 0-255");
		if (ft_atoi(data->c_arr[i]) > 255 || ft_atoi(data->c_arr[i]) < 0)
			printf_error(data, "Invalid RGB value 0-255");
		i++;
	}
}

void rgb_path_parse2(t_data *data)
{
	if (ft_strncmp(data->no, "NO ./path_north\n", 10) != 0)
		printf_error(data, "Invalid North Path");
	if (ft_strncmp(data->so, "SO ./path_south\n", 10) != 0)
		printf_error(data, "Invalid South Path");
	if (ft_strncmp(data->we, "WE ./path_west\n", 10) != 0)
		printf_error(data, "Invalid West Path");
	if (ft_strncmp(data->ea, "EA ./path_east\n", 10) != 0)
		printf_error(data, "Invalid East Path");
	if (ft_strncmp(data->f, "F ", 2) != 0)
		printf_error(data, "Invalid Floor RGB");
	if (ft_strncmp(data->c, "C ", 2) != 0)
		printf_error(data, "Invalid Roof RGB");
	data->f_arr = ft_split(data->f, ',');
	data->c_arr = ft_split(data->c, ',');
	rgb_path_parse3(data);
}

void rgb_path_parse1(t_data *data, char *b, int i)
{
	if (i == 0)
		data->no = give_mem_char(data->no, b);
	else if (i == 1)
		data->so = give_mem_char(data->so, b);
	else if (i == 2)
		data->we = give_mem_char(data->we, b);
	else if (i == 3)
		data->ea = give_mem_char(data->ea, b);
	else if (i == 5)
		data->f = give_mem_char(data->f, b);
	else if (i == 6)
		data->c = give_mem_char(data->c, b);
}
