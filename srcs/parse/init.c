#include "../../includes/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void map_rgb(t_data *data, t_texture *texture)
{
	char *arr;

	arr = data->f_arr[0];
	arr += 2;
	texture->floor = create_trgb(0, ft_atoi(arr), \
		ft_atoi(data->f_arr[1]), ft_atoi(data->f_arr[2]));
	arr = data->c_arr[0];
	arr += 2;
	texture->roof = create_trgb(0, ft_atoi(arr), \
		ft_atoi(data->c_arr[1]), ft_atoi(data->c_arr[2]));
}

void init_player(t_data *data, t_play *play)
{
	play->posX = data->player_x + 0.5;
	play->posY = data->player_y + 0.5;
	if (data->direction == NORTH)
	{
		play->dir_x = 0;
		play->dir_y = -1;
		play->plane_x = -0.66;
		play->plane_y = 0;
	}
	else if (data->direction == SOUTH)
	{
		play->dir_x = 0;
		play->dir_y = 1;
		play->plane_x = 0.66;
		play->plane_y = 0;
	}
	else if (data->direction == WEST)
	{
		play->dir_x = -1;
		play->dir_y = 0;
		play->plane_x = 0;
		play->plane_y = 0.66;
	}
	else
	{
		play->dir_x = 1;
		play->dir_y = 0;
		play->plane_x = 0;
		play->plane_y = -0.66;
	}
}

void	init_textured(t_data *data, t_texture *texture)
{
	texture->n = "./path_north";
	texture->s = "./path_south";
	texture->w = "./path_west";
	texture->e = "./path_east";
	map_rgb(data, texture);
}

void	init_structs(t_map *map)
{
	map->texture = malloc(sizeof(t_texture));
	map->play = malloc(sizeof(t_play));
	map->ray = malloc(sizeof(t_ray));
	map->mlx = malloc(sizeof(t_mlx));
	map->map = map->data->map;
	map->map[map->data->player_y][map->data->player_x] = '0';
	init_textured(map->data, map->texture);
	init_player(map->data, map->play);
}