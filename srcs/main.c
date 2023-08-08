#include "../includes/cub3d.h"

int ft_destroyer(t_map *map)
{
	//mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	//mlx_destroy_display(map->mlx_ptr);
	//free(map->mlx_ptr);
	free_structs_mlx(map);
	printf("Game finished!\n");
	exit(0);
}

void	move_player_right_left(t_map *map, int key_code)
{
	if (key_code == A_KEY)
	{
		if ((map->map[(int)map->play->pos_y][(int)(map->play->pos_x - \
					map->play->plane_x * PLAYER_SPEED)]) == '0')
			map->play->pos_x -= map->play->plane_x * PLAYER_SPEED;
		if (map->map[(int)(map->play->pos_y - map->play->plane_y * \
					PLAYER_SPEED)][(int)map->play->pos_x] == '0')
			map->play->pos_y -= map->play->plane_y * PLAYER_SPEED;
	}
	if (key_code == D_KEY)
	{
		if ((map->map[(int)map->play->pos_y][(int)(map->play->pos_x + \
					map->play->plane_x * PLAYER_SPEED)]) == '0')
			map->play->pos_x += map->play->plane_x * PLAYER_SPEED;
		if (map->map[(int)(map->play->pos_y + map->play->plane_y * \
					PLAYER_SPEED)][(int)map->play->pos_x] == '0')
			map->play->pos_y += map->play->plane_y * PLAYER_SPEED;
	}
}

void	move_player_up_down(t_map *map, int key_code)
{
	if (key_code == W_KEY)
	{
		if (map->map[(int)map->play->pos_y][(int)(map->play->pos_x + \
					map->play->dir_x * (double)PLAYER_SPEED)] == '0')
			map->play->pos_x += map->play->dir_x * (double)PLAYER_SPEED;
		if (map->map[(int)(map->play->pos_y + map->play->dir_y * \
					(double)PLAYER_SPEED)][(int)map->play->pos_x] == '0')
			map->play->pos_y += map->play->dir_y * (double)PLAYER_SPEED;
	}
	if (key_code == S_KEY)
	{
		if (map->map[(int)map->play->pos_y][(int)(map->play->pos_x - \
				map->play->dir_x * (double)PLAYER_SPEED)] == '0')
			map->play->pos_x -= map->play->dir_x * (double)PLAYER_SPEED;
		if (map->map[(int)(map->play->pos_y - map->play->dir_y * \
				PLAYER_SPEED)][(int)map->play->pos_x] == '0')
			map->play->pos_y -= map->play->dir_y * (double)PLAYER_SPEED;
	}
}

void	rotate_player_view(t_play *play, double rotate)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = play->dir_x;
	play->dir_x = play->dir_x * cos(rotate)
		- play->dir_y * sin(rotate);
	play->dir_y = old_dir_x * sin(rotate)
		+ play->dir_y * cos(rotate);
	old_plane_x = play->plane_x;
	play->plane_x = play->plane_x * cos(rotate)
		- play->plane_y * sin(rotate);
	play->plane_y = old_plane_x * sin(rotate)
		+ play->plane_y * cos(rotate);
}

int	ft_keys(int key_code, t_map *map)
{
	if (key_code == CLOSE)
		ft_destroyer(map);
	if (key_code == W_KEY || key_code == S_KEY)
		move_player_up_down(map, key_code);
	if (key_code == A_KEY || key_code == D_KEY)
		move_player_right_left(map, key_code);
	if (key_code == RIGHT)
		rotate_player_view(map->play, (double)-ROTATE_SPEED);
	if (key_code == LEFT)
		rotate_player_view(map->play, (double)ROTATE_SPEED);
	//raycaster_start(all);
	//mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
	return (0);
}

void ft_mlx_init(t_map *map)
{
	map->mlx = malloc(sizeof(t_mlx));
	map->mlx->mlx_ptr = mlx_init();
	map->mlx->win_ptr = mlx_new_window(map->mlx->mlx_ptr, WINDOW_X, WINDOW_Y, "Cub3D");
	map->mlx->img_to_window = mlx_new_image(map->mlx_ptr, WINDOW_X, WINDOW_Y);
	map->buffer = mlx_get_data_addr(map->mlx->img_to_window, map->mlx->&a, \
			map->mlx->&b, map->mlx->&c);
	mlx_loop(map->mlx->mlx_ptr);

	/*mlx = mlx_init();
	win = mlx_new_window(mlx, WINDOW_X, WINDOW_Y, "Cub3D");
	img = mlx_new_image(mlx, WINDOW_X, WINDOW_Y);
	addr = mlx_get_data_addr(img, &a,
			&b, &c);
	mlx_loop(mlx);*/
	/*int a;
	int b;
	int c;
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, WINDOW_X, WINDOW_Y, "Cub3d");
	map->img_ptr = mlx_new_image(map->win_ptr, WINDOW_X, WINDOW_Y);
	map->address = mlx_get_data_addr(map->img_ptr, &map->ray->bits, \
		&map->ray->line_len, \ &map->ray->end);
	//raycast(map);
	//mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
	mlx_do_key_autorepeaton(map->mlx_ptr);
	mlx_hook(map->win_ptr, 2, 1, ft_keys, map);
	mlx_hook(map->win_ptr, 33, (1L << 17), ft_destroyer, map);
	mlx_hook(map->win_ptr, 17, 1L << 17, ft_destroyer, map);
	mlx_loop(map->mlx_ptr);*/
}

int	main(int argc, char **argv)
{
	t_map			map;

	if (argc == 2)
	{
		map.data = malloc(sizeof(t_data));
		map.data->argv = argv;
		main_parse(map.data);
		init_structs(&map);
		printf_struct_map(&map);
		map.map = map.data->map;
		ft_mlx_init(&map);
		free_structs_mlx(&map);
	}
	else
	{
		printf("\e[1;31mERROR\n\e[0;0m");
		return (printf("The Number Of Arguments Must Be Only TWO"));
	}
}