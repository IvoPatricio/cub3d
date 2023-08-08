#include "../../includes/cub3d.h"

void free_map(t_data *data)
{
    int i;

    if (data->no)
    {
        free(data->no);
        data->no = NULL;
    }
    if (data->so)
    {
        free(data->so);
        data->so = NULL;
    }
    if (data->we)
    {
        free(data->we);
        data->we = NULL;
    }
    if (data->ea)
    {
        free(data->ea);
        data->ea = NULL;
    }
    if (data->f)
    {
        free(data->f);
        data->f = NULL;
    }
    if (data->c)
    {
        free(data->c);
        data->c = NULL;
    }
    if (data->map)
    {
        i = 0;
        while (data->map[i])
        {
            free(data->map[i]);
            data->map[i] = NULL;
            i++;
        }
        free(data->map);
        data->map = NULL;
    }
    free_rest(data);
}

void free_rest(t_data *data)
{
    int i;

    if (data->c_arr)
    {
        i = 0;
        while (data->c_arr[i])
        {
            free(data->c_arr[i]);
            data->c_arr[i] = NULL;
            i++;
        }
        free(data->c_arr);
        data->c_arr = NULL;
    }

    if (data->f_arr)
    {
        i = 0;
        while (data->f_arr[i])
        {
            free(data->f_arr[i]);
            data->f_arr[i] = NULL;
            i++;
        }
        free(data->f_arr);
        data->f_arr = NULL;
    }
}

void free_structs_mlx(t_map *map)
{
    free_map(map->data);
    if (map->data)
        free(map->data);
    if (map->ray)
        free(map->ray);
    if (map->play)
        free(map->play);
    if (map->texture)
        free(map->texture);
    exit (0);
}
