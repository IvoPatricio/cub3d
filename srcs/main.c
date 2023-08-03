#include "../includes/cub3d.h"

/*
void	my_mlx_pixel_put1(t_map *map, int x, int y, int color)
{
	char	*dst1;

	dst1 = map->addr1 + (y * map->line_length + x * (map->bits_per_pixel / 8));
	*(unsigned int*)dst1 = color;
}

void	my_mlx_pixel_put2(t_map *map, int x, int y, int color)
{
	char	*dst2;

	dst2 = map->addr2 + (y * map->line_length + x * (map->bits_per_pixel / 8));
	*(unsigned int*)dst2 = color;
}

void mlx_rgb(t_map *map, t_texturedir *texture)
{
	int	x;
	int	y;

	y = 0;
	//mlx_define_xpm(map);
	map->mlx_ptr = mlx_init();
	map->mlx_win_ptr = mlx_new_window(map->mlx_ptr, WINDOW_X, WINDOW_Y, "cub3d");
	//we might need to add another roof and floor with addr so theres no pixel tearing
	map->img_roof1 = mlx_new_image(map->mlx_ptr, WINDOW_X, WINDOW_Y / 2);
	map->addr1 = mlx_get_data_addr(map->img_roof1, &map->bits_per_pixel, \
        &map->line_length, &map->endian);
	map->img_floor1 = mlx_new_image(map->mlx_ptr, WINDOW_X, WINDOW_Y / 2);
	map->addr2 = mlx_get_data_addr(map->img_floor1, &map->bits_per_pixel, \
        &map->line_length, &map->endian);
	while (y < WINDOW_Y / 2)
	{
		x = 0;
		while (x < WINDOW_X)
		{
			my_mlx_pixel_put1(map, x, y, texture->roof);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->mlx_win_ptr, \
		map->img_roof1, 0, 0);
	y = 0;
	while (y < WINDOW_Y / 2)
	{
		x = 0;
		while (x < WINDOW_X)
		{
			my_mlx_pixel_put2(map, x, y, texture->floor);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->mlx_win_ptr, \
		map->img_floor1, 0, WINDOW_Y / 2);
	mlx_loop(map->mlx_ptr);
}


/*
int key_press(int keycode, t_map *map)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(0);
	}
	if (keycode == 119 || keycode == 65362)
	{
		if (map->map[map->y - 1][map->x] != '1')
			key_w(map);
	}
	if (keycode == 100 || keycode == 65363)
	{
		if (map->map[map->y][map->x + 1] != '1')
			key_d(map);
	}
	if (keycode == 115 || keycode == 65364)
	{
		if (map->map[map->y + 1][map->x] != '1')
			key_s(map);
	}
	if (keycode == 97 || keycode == 65361)
	{
		if (map->map[map->y][map->x - 1] != '1')
			key_a(map);
	}
	printf("%d\n", keycode);
	return (0);
}*/

int ft_destroyer(t_map *map)
{
	mlx_destroy_window(map->mlx, map->win);
	mlx_destroy_image(map->mlx, map->wall);
	mlx_destroy_image(map->mlx, map->enemy);
	mlx_destroy_image(map->mlx, map->player);
	mlx_destroy_image(map->mlx, map->black);
	mlx_destroy_display(map->mlx);
	free(map->mlx);
	//free_map(map->data);
	exit(0);
}

void mlx_image(t_map *map)
{
	int	z;

	z = 64;
	map->win = mlx_new_window(map->mlx, WINDOW_X, WINDOW_Y, "cub3d");
	map->wall = mlx_xpm_file_to_image(map->mlx, \
		"./sprites/wall.xpm", &z, &z);
	map->enemy = mlx_xpm_file_to_image(map->mlx, \
		"./sprites/enemy.xpm", &z, &z);
	map->player = mlx_xpm_file_to_image(map->mlx, \
		"./sprites/player.xpm", &z, &z);
	map->black = mlx_xpm_file_to_image(map->mlx, \
		"./sprites/black.xpm", &z, &z);
}

void draw_line(t_map *map, float x0, float y0, float x1, float y1, int RGB) 
{
    float	dx;
    float	dy;
	float	steps;
    float	x_increment;
    float	y_increment;
	int		i;

	i = -1;
	dx = x1 - x0;
	dy = y1 - y0;
	steps = fmax(fabs(dx), fabs(dy));
	x_increment = dx / steps;
	y_increment = dy / steps;
	x_increment = dx / steps;
    y_increment = dy / steps;
    while (i++ <= steps) 
        mlx_pixel_put(map->mlx, map->win, (int)(x0 + i * x_increment), \
			(int)(y0 + i * y_increment), RGB);
}

void draw_ray(t_map *map, int RGB)
{
	double i;

	i = 1;
	while (i < 5)
	{
		mlx_pixel_put(map->mlx, map->win, map->pixels_x + map->diff_x * i, map->pixels_y + map->diff_y * i, RGB);
		i = i + 0.1;
	}
}

void draw_player(t_map *map, int RGB)
{
	mlx_pixel_put(map->mlx, map->win, map->pixels_x - 1, map->pixels_y, RGB);
	mlx_pixel_put(map->mlx, map->win, map->pixels_x, map->pixels_y, RGB);
	mlx_pixel_put(map->mlx, map->win, map->pixels_x + 1, map->pixels_y, RGB);
	mlx_pixel_put(map->mlx, map->win, map->pixels_x -1, map->pixels_y - 1, RGB);
	mlx_pixel_put(map->mlx, map->win, map->pixels_x, map->pixels_y - 1, RGB);
	mlx_pixel_put(map->mlx, map->win, map->pixels_x + 1, map->pixels_y - 1, RGB);
	mlx_pixel_put(map->mlx, map->win, map->pixels_x -1, map->pixels_y + 1, RGB);
	mlx_pixel_put(map->mlx, map->win, map->pixels_x, map->pixels_y + 1, RGB);
	mlx_pixel_put(map->mlx, map->win, map->pixels_x + 1, map->pixels_y + 1, RGB);
}



float dist(float ax, float ay, float bx, float by, float an)
{
	return (sqrt(bx-ax) * (bx-ax) + (by-ay) * (by-ay));
}

void draw_3dray(t_map *map)
{
	int	r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo, hx, hy, vx, vy, disT;

	ra = map->angle;
	for (r = 0; r < 1; r++)
	{
		//-- CHECK HORIZONTAL LINE --//
		dof = 0;
		float disH = 10000000;
		hx = map->pixels_x;
		hy = map->pixels_y;
		float aTan = -1/tan(ra);
		// Looking DOWN //
		if (ra > PI)
		{
			ry = (((int)map->pixels_y/64)*64)-0.0001;
			rx = (map->pixels_y-ry)*aTan+map->pixels_x;
			yo = -64;
			xo = -yo*aTan;
		}
		// Looking UP //
		if (ra < PI)
		{
			ry = (((int)map->pixels_y/64)*64)+64;
			rx = (map->pixels_y-ry)*aTan+map->pixels_x;
			yo = 64;
			xo = -yo*aTan;
		}
		// Looking Straight
		if (ra == 0 || ra == PI)
		{
			rx = map->pixels_x;
			ry = map->pixels_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)/64;
			my = (int)(ry)/64;
			printf("%dMX\n", mx);
			printf("%dMY\n", my);
			mp = my * mx;
			if (mx < 0)
				mx = 0;
			else if (mx > 6)
				mx = 0;
			if (my < 0)
				my = 0;
			else if (my > 6)
				my = 6;
			if (map->map[my][mx] == '1' && mx <= 6 && mx >= 0 && my <= 6 && my >= 0 && mp > 0)
			{
				hx = rx;
				hy = ry;
				disH = dist(map->pixels_x, map->pixels_y, hx, hy, ra);
				dof = 8;
			}
			else
			{
				rx+=xo;
				ry+=yo;
				dof += 3;
			}
		}
		draw_line(map, map->pixels_x, map->pixels_y, rx + 10, ry, RGB_YELLOW);
		draw_line(map, map->pixels_x, map->pixels_y, rx - 10, ry, RGB_YELLOW);
		//-- CHECK VERTICAL LINE --//
		dof = 0;
		float disV = 10000000;
		vx = map->pixels_x;
		vy = map->pixels_y;
		float nTan = -tan(ra);
		// Looking DOWN //
		if (ra > P2 && ra < P3)
		{
			rx = (((int)map->pixels_x/64)*64)-0.0001;
			ry = (map->pixels_x-rx)*nTan+map->pixels_y;
			xo = -64;
			yo = -xo*nTan;
		}
		// Looking UP //
		if (ra < P2 || ra > P3)
		{
			rx = (((int)map->pixels_x/64)*64)+64;
			ry = (map->pixels_x-rx)*nTan+map->pixels_y;
			xo = 64;
			yo = -xo*nTan;
		}
		// Looking Straight
		if (ra == 0 || ra == PI)
		{
			rx = map->pixels_x;
			ry = map->pixels_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)/64;
			my = (int)(ry)/64;
			mp = my * mx;
			if (mx < 0)
				mx = 0;
			else if (mx > 6)
				mx = 0;
			if (my < 0)
				my = 0;
			else if (my > 6)
				my = 6;
			if (map->map[my][mx] == '1' && mx <= 6 && mx >= 0 && my <= 6 && my >= 0 && mp > 0)
			{
				vx = rx;
				vy = ry;
				disV = dist(map->pixels_x, map->pixels_y, vx, vy, ra);
				dof = 8;
			}
			else
			{
				rx+=xo;
				ry+=yo;
				dof += 3;
			}
		}
		draw_line(map, map->pixels_x, map->pixels_y, rx, ry, RGB_RED);
		/*if (disV < disH)
		{
			rx=vx;
			ry=vy;
			disT = disV;
		}
		if (disH < disV)
		{
			rx=hx;
			ry=hy;
			disT = disH;
		}
		// --DRAW 3D WALLS--//
		float lineH = (6*320)/disT;
		if (lineH>320)
			lineH=320;
		float lineO = 160-lineH/2;*/
		//mlx_pixel_put(map->mlx, map->win, rx, ry-5, RGB_YELLOW);
		//mlx_pixel_put(map->mlx, map->win, rx, ry, RGB_YELLOW);
	}
}

void key_w(t_map *map)
{
	map->x = (map->pixels_x + cos(map->angle) * PLAYER_SPEED) / 64;
    map->y = (map->pixels_y + sin(map->angle) * PLAYER_SPEED) / 64;
    if (map->map[map->y][map->x] != '1')
	{
    	draw_player(map, RGB_BLACK);
    	draw_ray(map, RGB_BLACK);
    	map->x = (map->pixels_x + map->diff_x) / 64;
    	map->y = (map->pixels_y + map->diff_y) / 64;
    	if (map->map[map->y][map->x] != '1') 
    	{
    		map->pixels_x += map->diff_x;
    		map->pixels_y += map->diff_y;
   		}
    	draw_player(map, RGB_WHITE);
    	draw_ray(map, RGB_YELLOW);
	}
}

void key_s(t_map *map)
{
	map->x = (map->pixels_x - cos(map->angle) * PLAYER_SPEED) / 64;
    map->y = (map->pixels_y - sin(map->angle) * PLAYER_SPEED) / 64;
    if (map->map[map->y][map->x] != '1')
	{
    	draw_player(map, RGB_BLACK);
    	draw_ray(map, RGB_BLACK);
    	map->x = (map->pixels_x - map->diff_x) / 64;
    	map->y = (map->pixels_y - map->diff_y) / 64;
    	if (map->map[map->y][map->x] != '1') 
    	{
        	map->pixels_x -= map->diff_x;
        	map->pixels_y -= map->diff_y;
    	}
    	draw_player(map, RGB_WHITE);	
		draw_ray(map, RGB_YELLOW);
	}
}

void key_d(t_map *map)
{
	map->x = (map->pixels_x + cos(map->angle - PI/2) * PLAYER_SPEED) / 64;
    map->y = (map->pixels_y + sin(map->angle - PI/2) * PLAYER_SPEED) / 64;
    if (map->map[map->y][map->x] != '1')
    {
    	draw_player(map, RGB_BLACK);
    	draw_ray(map, RGB_BLACK);
    	map->x = (map->pixels_x + cos(map->angle + PI/2) * PLAYER_SPEED) / 64;
    	map->y = (map->pixels_y + sin(map->angle + PI/2) * PLAYER_SPEED) / 64;
    	if (map->map[map->y][map->x] != '1') 
    	{
    	    map->pixels_x += cos(map->angle + PI/2) * PLAYER_SPEED;
        	map->pixels_y += sin(map->angle + PI/2) * PLAYER_SPEED;
    	}
    	draw_player(map, RGB_WHITE);
    	draw_ray(map, RGB_YELLOW);
	}
}

void key_a(t_map *map)
{
	map->x = (map->pixels_x + cos(map->angle + PI/2) * PLAYER_SPEED) / 64;
    map->y = (map->pixels_y + sin(map->angle + PI/2) * PLAYER_SPEED) / 64;
    if (map->map[map->y][map->x] != '1')
    {
    	draw_player(map, RGB_BLACK);
		draw_ray(map, RGB_BLACK);
		map->x = (map->pixels_x + cos(map->angle - PI/2) * PLAYER_SPEED) / 64;
    	map->y = (map->pixels_y + sin(map->angle - PI/2) * PLAYER_SPEED) / 64;
    	if (map->map[map->y][map->x] != '1') 
    	{
    	    map->pixels_x += cos(map->angle - PI/2) * PLAYER_SPEED;
        	map->pixels_y += sin(map->angle - PI/2) * PLAYER_SPEED;
    	}
    	draw_player(map, RGB_WHITE);
    	draw_ray(map, RGB_YELLOW);
	}
}

void arrow_w(t_map *map)
{
	draw_ray(map, RGB_BLACK);
	map->angle -= ROTATE_SPEED;
    if (map->angle < 0)
	    map->angle += 2 * PI;
	map->diff_x = cos(map->angle) * PLAYER_SPEED;
	map->diff_y = sin(map->angle) * PLAYER_SPEED;
    draw_ray(map, RGB_YELLOW);
}

void arrow_s(t_map *map)
{
	draw_ray(map, RGB_BLACK);
	map->angle += ROTATE_SPEED;
    if (map->angle > 2 * PI)
        map->angle -= 2 * PI;
    map->diff_x = cos(map->angle) * PLAYER_SPEED;
    map->diff_y = sin(map->angle) * PLAYER_SPEED;
	draw_ray(map, RGB_YELLOW);
}

void arrow_d(t_map *map)
{
	draw_ray(map, RGB_BLACK);
	map->angle += ROTATE_SPEED;
    if (map->angle > 2 * PI)
        map->angle -= 2 * PI;
    map->diff_x = cos(map->angle) * PLAYER_SPEED;
    map->diff_y = sin(map->angle) * PLAYER_SPEED;
    draw_ray(map, RGB_YELLOW);
	draw_3dray(map);
}

void arrow_a(t_map *map)
{
	draw_ray(map, RGB_BLACK);
	map->angle -= ROTATE_SPEED;
    if (map->angle < 0)
        map->angle += 2 * PI;
    map->diff_x = cos(map->angle) * PLAYER_SPEED;
    map->diff_y = sin(map->angle) * PLAYER_SPEED;
    draw_ray(map, RGB_YELLOW);
	draw_3dray(map);
}

int ft_key_press(int keycode, t_map *map)
{
    if (keycode == 65307)
        ft_destroyer(map);
    if (keycode == 119)
        key_w(map);
    if (keycode == 100)
        key_d(map);
    if (keycode == 115)
        key_s(map);
    if (keycode == 97)
        key_a(map);
    if (keycode == 65362)
		arrow_w(map);
    if (keycode == 65364)
        arrow_s(map);
    if (keycode == 65363)
		arrow_d(map);
    if (keycode == 65361)
		arrow_a(map);
    return (0);
}

void mlx_create(t_map *map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == WALL)
				mlx_put_image_to_window(map->mlx, map->win, \
					map->wall, x * 64, y * 64);
			else if (map->map[y][x] == 'N')
			{
				map->pixels_x = (x * 64);
				map->pixels_y = (y * 64);
				draw_player(map, RGB_WHITE);
				draw_ray(map, RGB_YELLOW);
			}
			x++;
		}
		y++;
	}
}

int ft_key_release(int keycode, t_map *map)
{
	return (0);
}

void ft_mlx_init(char **mapchar)
{
	t_map	map;

	ft_memset(&map, 0, (sizeof(map)));
	map.map = mapchar;
	map.diff_x = cos(map.angle) * PLAYER_SPEED;
	map.diff_y = sin(map.angle) * PLAYER_SPEED;
	map.mlx = mlx_init();
	mlx_image(&map);
	mlx_create(&map);
	mlx_hook(map.win, 17, 1L << 17, ft_destroyer, &map); //close with X
	mlx_hook(map.win, 2, 1L<<0, ft_key_press, &map);
	mlx_hook(map.win, 3, 1L<<1, ft_key_release, &map);
	mlx_loop(map.mlx);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_texturedir	texture;

	if (argc == 2)
	{
		ft_memset(&data, 0, (sizeof(data)));
		data.argv = argv;
		main_parse(&data);
		init(&data, &texture);

		//mlx_rgb(&map, &texture); //RGB ROOF & CELLING
		ft_mlx_init(data.map);
		free_map(&data);
	}
	else
	{
		printf("\e[1;31mERROR\n\e[0;0m");
		return (printf("The Number Of Arguments Must Be Only TWO"));
	}
	
}
