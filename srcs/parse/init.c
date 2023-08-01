#include "../../includes/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	map_rgb(t_data *data, t_texturedir *texture)
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

/*static void	init_character(t_character *character)
{
	character->position_x = 0.0;
	character->position_y = 0.0;
	character->direction_x = 0.0;
	character->direction_y = 0.0;
}*/

void	init_texturedir(t_data *data, t_texturedir *texture)
{
	texture->n = data->no;
	texture->s = data->so;
	texture->w = data->we;
	texture->e = data->ea;
	map_rgb(data, texture);
}

void	init(t_data *data, t_texturedir *texture)
{
	init_texturedir(data, texture);
	//init_character(character);
}