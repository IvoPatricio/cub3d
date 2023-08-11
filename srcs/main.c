#include "../includes/cub3d.h"

int ft_destroyer(t_map *map)
{
	mlx_destroy_window(map->mlx->mlx_ptr, map->mlx->win_ptr);
	mlx_destroy_image(map->mlx->mlx_ptr, map->mlx->img_to_window);
	mlx_destroy_display(map->mlx->mlx_ptr);
	free(map->mlx->mlx_ptr);
	free_structs_mlx(map);
	exit(1);
}

void ft_key_w(t_map *map, int key_code)
{
	double tempX;
	double tempY;

	tempX = map->play->posX;
	tempY = map->play->posY;
	if (key_code == W_KEY)
	{
		if (map->map[(int)map->play->posY][((int)map->play->posX + \
			(int)map->play->dir_x * (int)PLAYER_SPEED)] == FLOOR)
			map->play->posX += map->play->dir_x * PLAYER_SPEED;
			if (map->map[(int)map->play->posY][((int)map->play->posX + \
				(int)map->play->dir_x * (int)PLAYER_SPEED)] == WALL)
				map->play->posX = tempX;
		if (map->map[(int)(map->play->posY + (int)map->play->dir_y * \
			(int)PLAYER_SPEED)][(int)map->play->posX] == FLOOR)
			map->play->posY += map->play->dir_y * PLAYER_SPEED;
			if (map->map[(int)(map->play->posY + (int)map->play->dir_y * \
				(int)PLAYER_SPEED)][(int)map->play->posX] == WALL)
				map->play->posY = tempY;
	}
}

void ft_key_s(t_map *map, int key_code)
{
	double tempX;
	double tempY;

	tempX = map->play->posX;
	tempY = map->play->posY;
	if (key_code == S_KEY)
	{
		if (map->map[(int)map->play->posY][((int)map->play->posX - \
			(int)map->play->dir_x * (int)PLAYER_SPEED)] == FLOOR)
			map->play->posX -= map->play->dir_x * PLAYER_SPEED;
			if (map->map[(int)map->play->posY][((int)map->play->posX - \
				(int)map->play->dir_x * (int)PLAYER_SPEED)] == WALL)
				map->play->posX = tempX;
		if (map->map[((int)map->play->posY - (int)map->play->dir_y * \
			(int)PLAYER_SPEED)][(int)map->play->posX] == FLOOR)
			map->play->posY -= map->play->dir_y * PLAYER_SPEED;
			if (map->map[((int)map->play->posY - (int)map->play->dir_y * \
				(int)PLAYER_SPEED)][(int)map->play->posX] == WALL)
				map->play->posY = tempY;
	}
}

void ft_key_a(t_map *map, int key_code)
{
	double tempX;
	double tempY;

	tempX = map->play->posX;
	tempY = map->play->posY;
	if (key_code == A_KEY)
	{
		if ((map->map[(int)map->play->posY][((int)map->play->posX - \
			(int)map->play->plane_x * (int)PLAYER_SPEED)]) == FLOOR)
			map->play->posX -= map->play->plane_x * PLAYER_SPEED;
			if ((map->map[(int)map->play->posY][((int)map->play->posX - \
				(int)map->play->plane_x * (int)PLAYER_SPEED)]) == WALL)
				map->play->posX = tempX;
		if (map->map[((int)map->play->posY - (int)map->play->plane_y * \
			(int)PLAYER_SPEED)][(int)map->play->posX] == FLOOR)
			map->play->posY -= map->play->plane_y * PLAYER_SPEED;
			if (map->map[((int)map->play->posY - (int)map->play->plane_y * \
			(int)PLAYER_SPEED)][(int)map->play->posX] == WALL)
				map->play->posY = tempY;
	}
}

void ft_key_d(t_map *map, int key_code)
{
	double tempX;
	double tempY;

	tempX = map->play->posX;
	tempY = map->play->posY;
	if (key_code == D_KEY)
	{
		if ((map->map[(int)map->play->posY][((int)map->play->posX + \
			(int)map->play->plane_x * (int)PLAYER_SPEED)]) == FLOOR)
			map->play->posX += map->play->plane_x * PLAYER_SPEED;
			if ((map->map[(int)map->play->posY][((int)map->play->posX + \
			(int)map->play->plane_x * (int)PLAYER_SPEED)]) == WALL)
				map->play->posX = tempX;
		if (map->map[((int)map->play->posY + (int)map->play->plane_y * \
			(int)PLAYER_SPEED)][(int)map->play->posX] == FLOOR)
			map->play->posY += map->play->plane_y * PLAYER_SPEED;
			if (map->map[((int)map->play->posY + (int)map->play->plane_y * \
			(int)PLAYER_SPEED)][(int)map->play->posX] == WALL)
				map->play->posY = tempY;
	}
}

void ft_key_angle(t_play *play, double rotate)
{
	double	old_dir_x;
	double	old_plane_x;

	printf_struct_player(play);
	old_dir_x = play->dir_x;
	play->dir_x = play->dir_x * cos(rotate) - play->dir_y * sin(rotate);
	play->dir_y = old_dir_x * sin(rotate) + play->dir_y * cos(rotate);
	old_plane_x = play->plane_x;
	play->plane_x = play->plane_x * cos(rotate) - play->plane_y * sin(rotate);
	play->plane_y = old_plane_x * sin(rotate) + play->plane_y * cos(rotate);
	printf_struct_player(play);
}

void	ft_pixel_drawing(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->buffer + (y * mlx->b + x * (mlx->a / 8));
	*(unsigned int *) dst = color;
}

void	draw_texture(t_map *map, int x, int color)
{
	int	y;

	y = map->ray->drawstart;
	while (y < map->ray->drawend)
	{
		ft_pixel_drawing(map->mlx, x, y, color);
		y++;
	}
}

void	draw_walls(t_map *map, int x)
{
	if (map->ray->side == 1)
	{
		if (map->ray->stepy < 0)
			draw_texture(map, x, 0xFF0000);
		else 
			draw_texture(map, x, 0x00FF00);
	}
	if (map->ray->side == 0)
	{
		if (map->ray->stepx < 0)
			draw_texture(map, x, 0x0000FF);
		else 
			draw_texture(map, x, 0x000000);
	}
}

void draw_background(t_map *map, int x)
{
	int	y;

	y = 0;
	while (y < WIN_Y)
	{
		if (y < map->ray->drawstart)
			ft_pixel_drawing(map->mlx, x, y, map->texture->roof);
		else if (y >= map->ray->drawend)
			ft_pixel_drawing(map->mlx, x, y, map->texture->floor);
		y++;
	}
}

void raycast_dda(t_map *map)
{
	t_ray	*ray;

	ray = map->ray;
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepy;
			ray->side = 1;
		}
		if (map->map[ray->mapY][ray->mapX] == WALL)
			ray->hit = 1;
		if (ray->side == 0)
		{
			ray->walldist = ray->sideDistX - ray->deltaDistX;
		}
		else
			ray->walldist =  ray->sideDistY - ray->deltaDistY;
		
		ray->line_height = (int)(WIN_Y / ray->walldist);

		ray->drawstart = -ray->line_height / 2 + WIN_Y / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;

		ray->drawend = ray->line_height / 2 + WIN_Y / 2;
		if (ray->drawend >=  WIN_Y)
			ray->drawend = WIN_Y - 1;
	}
	if (ray->side == 0)
		ray->wallhit = map->play->posY + ray->walldist * ray->rayDirY;
	else
		ray->wallhit = map->play->posX + ray->walldist * ray->rayDirX;
	ray->wallhit -= floor(ray->wallhit);
	 //x coordinate on the texture
    /*  int texX = int(wallX * double(texWidth));
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1*/
}

void raycast_2(t_map *map)
{
	t_ray	*ray;

	ray = map->ray;
	if (ray->rayDirX < 0)
	{
		ray->stepx = -1;
		ray->sideDistX = (map->play->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepx = 1;
		ray->sideDistX = (ray->mapX + 1.0 - map->play->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepy = -1;
		ray->sideDistY = (map->play->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepx = 1;
		ray->sideDistY = (ray->mapY + 1.0 - map->play->posY) * ray->deltaDistY;
	}
	raycast_dda(map);
}

void raycast_1(t_map *map, int i)
{
	t_ray	*ray;

	ray = map->ray;
	ray->cameraX = 2 * i /(double)WIN_X-1;
	ray->rayDirX = map->play->dir_x + map->play->plane_x * ray->cameraX;
	ray->rayDirY = map->play->dir_y + map->play->plane_y * ray->cameraX;
	ray->mapX = (int)map->play->posX;
	ray->mapY = (int)map->play->posY;
	ray->deltaDistX = sqrt(1 + (ray->rayDirY* ray->rayDirY) \
		/ (ray->rayDirX * ray->rayDirX));
	ray->deltaDistY = sqrt(1 + (ray->rayDirX * ray->rayDirX) \
		/ (ray->rayDirY * ray->rayDirY));
	raycast_2(map);
}

void raydrawing(t_map *map)
{
	int x;

	x = 0;
	while (x < WIN_X)
	{
		raycast_1(map, x);
		draw_background(map, x);
		draw_walls(map, x);
		x++;
	}
	mlx_put_image_to_window(map->mlx->mlx_ptr, map->mlx->win_ptr, \
		map->mlx->img_to_window, 0, 0);
}

int	ft_keys(int key_code, t_map *map)
{
	if (key_code == CLOSE)
		ft_destroyer(map);
	if (key_code == W_KEY)
		ft_key_w(map, key_code);
	if (key_code == S_KEY)
		ft_key_s(map, key_code);
	if (key_code == A_KEY)
		ft_key_a(map, key_code);
	if (key_code == D_KEY)
		ft_key_d(map, key_code);
	if (key_code == RIGHT)
		ft_key_angle(map->play, -(double)ROTATE_SPEED);
	if (key_code == LEFT)
		ft_key_angle(map->play, (double)ROTATE_SPEED);
	raydrawing(map);
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
			printf("Error\nMlx_Buffer Allocation Failed");
			free_structs_mlx(map);
		}
		raydrawing(map);
		mlx_hook(map->mlx->win_ptr, 2, 1, ft_keys, map);
		mlx_hook(map->mlx->win_ptr, 17, 1L << 17, ft_destroyer, map);
		mlx_hook(map->mlx->win_ptr, 33, 1L << 17, ft_destroyer, map);
		mlx_loop(map->mlx->mlx_ptr);
	}
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 2)
	{
		map.data = malloc(sizeof(t_data));
		struct_malloc_error(&map, map.data, sizeof(map.data));
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