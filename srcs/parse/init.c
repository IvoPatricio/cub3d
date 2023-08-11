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
		printf("-----------NORTH-----------\n\n");
		play->dir_x = 0;
		play->dir_y = -1;
		play->plane_x = -0.66;
		play->plane_y = 0;
	}
	else if (data->direction == SOUTH)
	{
		printf("-----------SOUTH-----------\n\n");
		play->dir_x = 0;
		play->dir_y = 1;
		play->plane_x = 0.66;
		play->plane_y = 0;
	}
	else if (data->direction == EAST)
	{
		printf("-----------EAST-----------\n\n");
		play->dir_x = -1;
		play->dir_y = 0;
		play->plane_x = 0;
		play->plane_y = 0.66;
	}
	else if (data->direction == WEST)
	{
		printf("-----------WEST-----------\n\n");
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
	if (data->direction == NORTH)
		texture->p_text = NORTH;
	else if (data->direction == SOUTH)
		texture->p_text = SOUTH;
	else if (data->direction == EAST)
		texture->p_text = EAST;
	else if ((data->direction == WEST))
		texture->p_text = WEST;
	map_rgb(data, texture);
}

void	init_structs(t_map *map)
{
	map->texture = malloc(sizeof(t_texture));
	struct_malloc_error(map, map->texture, sizeof(map->texture));
	map->play = malloc(sizeof(t_play));
	struct_malloc_error(map, map->play, sizeof(map->play));
	map->ray = malloc(sizeof(t_ray));
	struct_malloc_error(map, map->ray, sizeof(map->ray));
	map->mlx = malloc(sizeof(t_mlx));
	struct_malloc_error(map, map->mlx, sizeof(map->mlx));
	map->map = map->data->map;
	map->map[map->data->player_y][map->data->player_x] = '0';
	init_textured(map->data, map->texture);
	init_player(map->data, map->play);
}