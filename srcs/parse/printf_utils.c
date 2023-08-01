#include "../../includes/cub3d.h"

void printf_error(t_data *data, const char *str)
{
	printf("\e[1;31mERROR\n\e[0;0m");
	printf("\e[0;34m%s\n\e[0;0m", str);
	free_map(data);
}

void printf_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arr)
	{
		printf("%s", data->map[i]);
		i++;
	}
	printf("\n");
}

void printf_paths(t_data *data)
{
	int	i;

	printf("%s", data->no);
	printf("%s", data->so);
	printf("%s", data->we);
	printf("%s", data->ea);
	i = 0;
	while (data->f_arr[i])
		printf("%s\n", data->f_arr[i++]);
	i = 0;
	while (data->c_arr[i])
		printf("%s\n", data->c_arr[i++]);
}
