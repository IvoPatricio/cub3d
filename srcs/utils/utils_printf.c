#include "../../includes/cub3d.h"

void printf_error(t_data *data, const char *str)
{
	perror("\e[1;31mERROR");  
	printf("\e[0;0m\e[0;34m%s\n\e[0;0m", str);
	free_map(data);
	exit(0);
}

void printf_map(t_data *data)
{
	int	i;

	i = 0;
	printf("--------\e[1;34mMATRIX_MAP\033[0m--------");
	while (i < data->arr)
	{
		printf("%s", data->map[i]);
		i++;
	}
}

void printf_paths(t_data *data)
{
	int	i;

	printf("Path_North:%s\n", data->no);
	printf("Path_South:%s\n", data->so);
	printf("Path_West:%s\n", data->we);
	printf("Path_East:%s\n", data->ea);
	i = 0;
	printf("-----RGB-----\n");
	while (data->f_arr[i])
		printf("%s\n", data->f_arr[i++]);
	i = 0;
	while (data->c_arr[i])
		printf("%s\n", data->c_arr[i++]);
}

void printf_struct_map(t_map *map)
{
	printf("\n---------\e[1;34mTEXTURES\033[0m---------");
	printf("\nTexture_East:%s\n", map->texture->e);
	printf("Texture_North:%s\n", map->texture->n);
	printf("Texture_South:%s\n", map->texture->s);
	printf("Texture_West:%s\n", map->texture->w);
	printf("RGB-Texture->floor:%d\n", map->texture->floor);
	printf("RGB-Texture->roof:%d\n\n", map->texture->roof);
	printf("      \e[1;34mMAIN-TEXTURE:\033[0m%c\n", \
		map->texture->player_direction);
	printf("--------------------------\n");
}

void printf_struct_player(t_play *play)
{
	printf("\n\n---------------\n\n");
	printf("%fplay->dir_x\n", play->dir_x);
	printf("%fplay->dir_y\n", play->dir_y);
	printf("%fplay->old_dir_x\n", play->old_dir_x);
	printf("%fplay->old_plane_x\n", play->old_plane_x);
	printf("%fplay->plane_x\n", play->plane_x);
	printf("%fplay->plane_y\n", play->plane_y);
	printf("%fplay->posX\n", play->posX);
	printf("%fplay->posY\n", play->posY);
	printf("\n\n---------------\n\n");
}
