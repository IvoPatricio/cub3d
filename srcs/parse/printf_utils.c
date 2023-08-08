#include "../../includes/cub3d.h"

void printf_error(t_data *data, const char *str)
{
	printf("\e[1;31mERROR\n\e[0;0m");
	printf("\e[0;34m%s\n\e[0;0m", str);
	free_map(data);
	exit(0);
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

void printf_struct_map(t_map *map)
{
	printf("map->play->dir_x: %f\n", map->play->dir_x);
	printf("map->play->dir_y:%f\n", map->play->dir_y);
	printf("map->play->plane_x:%f\n", map->play->plane_x);
	printf("map->play->plane_y:%f\n", map->play->plane_y);
	printf("map->play->pos_x:%f\n", map->play->pos_x);
	printf("map->play->pos_y:%f\n", map->play->pos_y);
	printf("map->texture->e:%s\n", map->texture->e);
	printf("map->texture->n:%s\n", map->texture->n);
	printf("map->texture->s:%s\n", map->texture->s);
	printf("map->texture->w:%s\n", map->texture->w);
	printf("map->texture->floor:%d\n", map->texture->floor);
	printf("map->texture->roof:%d\n", map->texture->roof);

}
