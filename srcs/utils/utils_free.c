#include "../../includes/cub3d.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->argv)
	{
		while (data->argv[i])
		{
			free(data->argv[i]);
			i++;
		}
		free(data->argv);
	}
	if (data->map)
		free(data->map);
	if (data)
    	free(data);
}

void	free_structs_mlx(t_map *map)
{
	free_map(map->data);
	if (map->ray)
		free(map->ray);
	if (map->play)
		free(map->play);
	if (map->texture)
		free(map->texture);
	if (map->mlx)
		free(map->mlx);
	exit(0);
}
