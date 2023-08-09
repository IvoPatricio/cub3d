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
	printf("--------\e[1;34mMATRIX_MAP\033[0m--------\n");
	while (i < data->arr)
	{
		printf("%s", data->map[i]);
		i++;
	}
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
	printf("---------\e[1;34mTEXTURES\033[0m---------");
	printf("\nTexture_East:%s\n", map->texture->e);
	printf("Texture_North:%s\n", map->texture->n);
	printf("Texture_South:%s\n", map->texture->s);
	printf("Texture_West:%s\n", map->texture->w);
	printf("RGB-Texture->floor:%d\n", map->texture->floor);
	printf("RGB-Texture->roof:%d\n\n", map->texture->roof);
	printf("      \e[1;34mMAIN-TEXTURE:\033[0m%c\n", \
		map->texture->p_text);
	printf("--------------------------\n");

}
