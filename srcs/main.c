#include "../includes/cub3d.h"

int ft_destroyer(t_map *map)
{
	mlx_destroy_window(map->mlx->mlx_ptr, map->mlx->win_ptr);
	mlx_destroy_image(map->mlx->mlx_ptr, map->mlx->img_to_window);
	mlx_destroy_display(map->mlx->mlx_ptr);
	free(map->mlx->mlx_ptr);
	free_structs_mlx(map);
}

void	move_player_right_left(t_map *map, int key_code)
{
	if (key_code == A_KEY)
	{
		if ((map->map[(int)map->play->posY][(int)(map->play->posX - \
					map->play->plane_x * PLAYER_SPEED)]) == '0')
			map->play->posX -= map->play->plane_x * PLAYER_SPEED;
		if (map->map[(int)(map->play->posY - map->play->plane_y * \
					PLAYER_SPEED)][(int)map->play->posX] == '0')
			map->play->posY -= map->play->plane_y * PLAYER_SPEED;
	}
	if (key_code == D_KEY)
	{
		if ((map->map[(int)map->play->posY][(int)(map->play->posX + \
					map->play->plane_x * PLAYER_SPEED)]) == '0')
			map->play->posX += map->play->plane_x * PLAYER_SPEED;
		if (map->map[(int)(map->play->posY + map->play->plane_y * \
					PLAYER_SPEED)][(int)map->play->posX] == '0')
			map->play->posY += map->play->plane_y * PLAYER_SPEED;
	}
}

void	move_player_up_down(t_map *map, int key_code)
{
	if (key_code == W_KEY)
	{
		if (map->map[(int)map->play->posY][(int)(map->play->posX + \
					map->play->dir_x * (double)PLAYER_SPEED)] == '0')
			map->play->posX += map->play->dir_x * (double)PLAYER_SPEED;
		if (map->map[(int)(map->play->posY + map->play->dir_y * \
					(double)PLAYER_SPEED)][(int)map->play->posX] == '0')
			map->play->posY += map->play->dir_y * (double)PLAYER_SPEED;
	}
	if (key_code == S_KEY)
	{
		if (map->map[(int)map->play->posY][(int)(map->play->posX - \
				map->play->dir_x * (double)PLAYER_SPEED)] == '0')
			map->play->posX -= map->play->dir_x * (double)PLAYER_SPEED;
		if (map->map[(int)(map->play->posY - map->play->dir_y * \
				PLAYER_SPEED)][(int)map->play->posX] == '0')
			map->play->posY -= map->play->dir_y * (double)PLAYER_SPEED;
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

void ft_image(t_map *map)
{
	int	x;
	int	y;

	x =  100;
	y =	 100;
	map->aaa = mlx_xpm_file_to_image(map->mlx->mlx_ptr, \
		"./sprites/east_wall.xpm", &x, &y);
	mlx_put_image_to_window(map->mlx->mlx_ptr, map->mlx->win_ptr, map->aaa, 0, 0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->buffer + (y * mlx->b + x * (mlx->a / 8));
	*(unsigned int *) dst = color;
}

void draw_floor_roof(t_map *map, int x)
{
	int	y;

	y = 0;
	while (y < WIN_Y)
	{
		if (y < map->ray->draw_start)
			my_mlx_pixel_put(map->mlx, x, y, map->texture->roof);
		else if (y >= map->ray->draw_end)
			my_mlx_pixel_put(map->mlx, x, y, map->texture->floor);
		y++;
	}
}

void print_raycast(int x, t_map *map)
{
	if (map->ray->side == 0)
		map->ray->wall_x = map->play->posY + map->ray->perp_wall_dist * map->ray->rayDirY;
	else
		map->ray->wall_x = map->play->posX + map->ray->perp_wall_dist * map->ray->rayDirX;
	map->ray->wall_x -= floor(map->ray->wall_x);
	//draw_textures_on_walls(map, x);
	draw_floor_roof(map, x);
}

void raycast_dda(t_map *map)
{
	t_ray	*ray;

	ray = map->ray;
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->s_dist_x < ray->s_dist_y)
		{
			ray->s_dist_x += ray->delt_dist_x;
			ray->mapX += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->s_dist_y += ray->delt_dist_y;
			ray->mapY += ray->step_y;
			ray->side = 1;
		}
		if (map->map[ray->mapY][ray->mapX] == WALL)
			ray->hit = 1;
		if (ray->side == 0)
			ray->perp_wall_dist = ray->s_dist_x - ray->delt_dist_x;
		else
			ray->perp_wall_dist =  ray->s_dist_y - ray->delt_dist_y;
		ray->line_height = (int)(WIN_Y / ray->perp_wall_dist);
		ray->draw_start = -ray->line_height / 2 + WIN_Y / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + WIN_Y / 2;
		if (ray->draw_end >=  WIN_Y)
			ray->draw_end = WIN_Y - 1;
	}
}

void raycast_2(t_map *map)
{
	t_ray	*ray;

	ray = map->ray;
	if (ray->rayDirX < 0)
	{
		ray->step_x = -1;
		ray->s_dist_x = (map->play->posX - ray->mapX) * ray->delt_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->s_dist_x = (ray->mapX + 1.0 - map->play->posX) * ray->delt_dist_x;
	}
	if (ray->rayDirY < 0)
	{
		ray->step_y = -1;
		ray->s_dist_y = (map->play->posY - ray->mapY) * ray->delt_dist_y;
	}
	else
	{
		ray->step_x = 1;
		ray->s_dist_y = (ray->mapY + 1.0 - map->play->posY) * ray->delt_dist_y;
	}
	raycast_dda(map);
}

void raycast(t_map *map)
{
	t_ray	*ray;
	int	x;

	x = 0;
	ray = map->ray;
	while (x < WIN_X)
	{
		ray->cameraX = 2 * x /(double)WIN_X-1;
		ray->rayDirX = map->play->dir_x + map->play->plane_x * ray->cameraX;
		ray->rayDirY = map->play->dir_y + map->play->plane_y * ray->cameraX;
		ray->mapX = (int)map->play->posX;
		ray->mapY = (int)map->play->posY;
		ray->delt_dist_x = sqrt(1 + (ray->rayDirY* ray->rayDirY) \
			/ (ray->rayDirX * ray->rayDirX));
		ray->delt_dist_y = sqrt(1 + (ray->rayDirX * ray->rayDirX) \
			/ (ray->rayDirY * ray->rayDirY));
		raycast_2(map);
		print_raycast(x, map);
		x++;
	}
}

int	ft_keys(int key_code, t_map *map)
{
	map->mlx->i = 1;
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
	raycast(map);
	mlx_put_image_to_window(map->mlx->mlx_ptr, map->mlx->win_ptr, \
		map->mlx->img_to_window, 0, 0);
	return (0);
}

void ft_mlx_init(t_map *map)
{
	map->mlx->mlx_ptr = mlx_init();
	if (map->mlx->mlx_ptr != 0)
	{
		map->mlx->win_ptr = mlx_new_window(map->mlx->mlx_ptr, WIN_X, WIN_Y, "3D");
		map->mlx->img_to_window = mlx_new_image(map->mlx->mlx_ptr, WIN_X, WIN_Y);
		map->mlx->buffer = mlx_get_data_addr(map->mlx->img_to_window, &map->mlx->a,
			&map->mlx->b, &map->mlx->c);
		if (!map->mlx->buffer)
		{
			
			free_structs_mlx(map);
		}
		raycast(map);
		mlx_put_image_to_window(map->mlx->mlx_ptr, map->mlx->win_ptr, \
			map->mlx->img_to_window, 0, 0);
		mlx_do_key_autorepeaton(map->mlx->mlx_ptr);
		mlx_hook(map->mlx->win_ptr, 2, 1, ft_keys, map);
		mlx_hook(map->mlx->win_ptr, 33, (1L << 17), ft_destroyer, map);
		mlx_hook(map->mlx->win_ptr, 17, 1L << 17, ft_destroyer, map);
		mlx_loop(map->mlx->mlx_ptr);
	}
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
		ft_mlx_init(&map);
		free_structs_mlx(&map);
	}
	else
	{
		printf("\e[1;31mERROR\n\e[0;0m");
		return (printf("The Number Of Arguments Must Be Only TWO"));
	}
}