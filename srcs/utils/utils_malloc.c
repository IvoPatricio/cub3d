#include "../../includes/cub3d.h"

void string_malloc_error(t_data *data, char *a)
{
    if (!a)
        printf_error(data, "String Allocation Failed");
}

void array_malloc_error(t_data *data, char **a)
{
    if (!a)
        printf_error(data, "Array Allocation Failed");
}

void struct_malloc_error(t_map *map, const void *random, size_t size)
{
    if (!random)
    {
        printf("\e[1;31mERROR\n\e[0;0m");
	    printf("\e[0;34m\n\e[0;0m Struct Allocation Failed");
        free_structs_mlx(map);
    }
}