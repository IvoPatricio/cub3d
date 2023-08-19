/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire- <ifreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:45:02 by ifreire-          #+#    #+#             */
/*   Updated: 2023/08/19 07:04:12 by ifreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define BUFFER_SIZE 1

// GAME SETTINGS //
# define WIN_X 800
# define WIN_Y 640
# define ROTATE_SPEED 0.3
# define PLAYER_SPEED 0.1
# define MOUSE_SPEED 1

# define RGB_WHITE 0xFFFFFF
# define RGB_BLACK 0x000000
# define RGB_YELLOW 0xFFFF00

# define SPACE 32
# define WALL 49
# define FLOOR 48
# define NORTH 78
# define EAST 69
# define WEST 87
# define SOUTH 83

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define RIGHT 65363
# define LEFT 65361
# define CLOSE 65307

# include "../mini-linux/mlx.h"
# include "../srcs/utils/get_next_line/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_data		t_data;
typedef struct s_map		t_map;
typedef struct s_ray		t_ray;
typedef struct s_play		t_play;
typedef struct s_texture	t_texture;
typedef struct s_mlx		t_mlx;

typedef struct s_map
{
	char					**map;
	int						mousex;
	int						mousey;				
	t_play					*play;
	t_ray					*ray;
	t_texture				*texture;
	t_data					*data;
	t_mlx					*mlx;
}							t_map;

typedef struct s_mlx
{
	void					*mlx_ptr;
	void					*win_ptr;
	void					*img_to_window;
	char					*buffer;
	int						i;
	int						a;
	int						b;
	int						c;
	int						y;
	int						x;
}							t_mlx;

typedef struct s_play
{
	double					pos_x;
	double					pos_y;
	double					dir_x;
	double					dir_y;
	double					old_dir_x;
	double					old_plane_x;
	double					plane_x;
	double					plane_y;
	t_map					*map;
}							t_play;

typedef struct s_ray
{
	double					camera_x;
	double					raydir_x;
	double					raydir_y;
	double					deltadist_x;
	double					deltadist_y;
	double					sidedist_x;
	double					sidedist_y;
	double					walldist;
	double					wallhit;
	double					step;
	int						map_x;
	int						map_y;
	int						stepx;
	int						stepy;
	int						hit;
	int						side;
	int						line_height;
	int						drawstart;
	int						drawend;
}							t_ray;

typedef struct s_data
{
	char					**argv;
	int						arr;
	char					**map;
	char					*f;
	char					*c;
	char					**f_arr;
	char					**c_arr;
	char					*no;
	char					*so;
	char					*we;
	char					*ea;
	char					direction;
	int						player_x;
	int						player_y;
	int						map_time;
}							t_data;

typedef struct s_texture
{
	char					*n;
	char					*s;
	char					*w;
	char					*e;
	char					player_direction;
	int						roof;
	int						floor;
	int						x;
	int						y;
	t_mlx					*north;
	t_mlx					*south;
	t_mlx					*east;
	t_mlx					*west;
	t_mlx					*minimap;
}							t_texture;

typedef struct s_character
{
	double					position_x;
	double					position_y;
	double					direction_x;
	double					direction_y;
}							t_character;

// EXECUTE FUNCTIONS //
int							main(int argc, char **argv);
void						ft_mlx_init(t_map *map);
int							mouse_hook(t_map *map);


// init_rgb.c //
int							create_trgb(int t, int r, int g, int b);
void						map_rgb(t_data *data, t_texture *texture);

// init_textures_of_mlx.c //
void						ft_alloc_textures_utils(t_map *map, t_mlx *texture,
								char *path);
void						ft_init_alloc_textures(t_map *map);

// init_textures_of_player.c //
void						init_player1(t_data *data, t_play *play);
void						init_player_rest(t_data *data, t_play *play);
void						init_textured(t_data *data, t_texture *texture);
void						init_structs(t_map *map);

// mlx_angle_close.c//
void						ft_destroy_images_display_free(t_map *map);
int							ft_destroyer(t_map *map);
void						ft_key_angle(t_map *map, double rotate);

// mlx_draw_raycast.c//
void						draw_wall_textures(t_map *map, t_mlx *texture,
								int x);
void						draw_wall_colors(t_map *map, int x, int y, 
								int color);
void						draw_roof_floor(t_map *map, int x);
void						raydrawing(t_map *map);

// mlx_draw_minimap.c //
void						draw_minimap_colors(t_map *map, int x, int y, \
								int color);
void						minimap(t_map *map);

// mlx_keys.c//
void						ft_key_w(t_map *map, int key_code);
void						ft_key_s(t_map *map, int key_code);
void						ft_key_a(t_map *map, int key_code);
void						ft_key_d(t_map *map, int key_code);
int							ft_keys(int key_code, t_map *map);

// mlx_put_pixel.c//
void						ft_pixel_drawing(t_mlx *mlx, int x, int y,
								int color);
unsigned int				ft_get_pixel_color(t_mlx *mlx, int x, int y);

// raycast_lodev_dda.c//
void						raycast_rest_dda(t_map *map);
void						raycast_dda(t_map *map);
void						raycast_2(t_map *map);
void						raycast_1(t_map *map, int i);

// PARSE FUNCTIONS //
// init.c //

void						init_structs(t_map *map);
void						init_textured(t_data *data, t_texture *texture);
void						init_player_rest(t_data *data, t_play *play);
void						init_player1(t_data *data, t_play *play);
int							create_trgb(int t, int r, int g, int b);
void						map_rgb(t_data *data, t_texture *texture);

// free_utils.c //
void						free_map(t_data *data);
void						free_rest_map(t_data *data);
void						free_structs_mlx(t_map *map);
void						struct_malloc_error(t_map *map, const void *random,
								size_t size);
void						string_malloc_error(t_data *data, char *a);
void						array_malloc_error(t_data *data, char **a);

// printf_utils.c //
void						printf_error(t_data *data, const char *str);
void						printf_map(t_data *data);
void						printf_paths(t_data *data);
void						printf_struct_map(t_map *map);
void						printf_struct_player(t_play *play);

// main_parse.c //
int							parse_map_chars_utils(t_data *data, int x, int y,
								int c);
void						parse_map_caracthers(t_data *data);
char						*isspace_file2(t_data *data, char *str, int ind,
								int i);
char						*isspace_file1(t_data *data, int ind, int z);
void						paths_creation_parse(t_data *data);
int							path_utils(char *str);
void						check_if_path_valid(t_data *data);
char						*path_creation(t_data *data, int i, int value);
void						map_creation(t_data *data, int i);
int							parse_path(t_data *data);
void						file_name_parse(t_data *data);
void						reading_file(t_data *data, int fd, int index);
void						file_array(t_data *data);
void						init_data(t_data *data, char **argv);
void						main_parse(t_data *data, char **argv);
void						paths_parse_caracthers(t_data *data, int i);
void						map_flood_fill(t_data *data);
void						map_closed_by_walls(t_data *data, int x, int y);
int							*map_vector_dy(void);
int							*map_vector_dx(void);

// parse_utils.c //
void						*ft_memset(void *b, int c, size_t len);
size_t						ft_lenspace(const char *str);
size_t						ft_strlen(const char *str);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
int							ft_atoi(const char *str);
int							ft_isdigit(int c);
int							ft_isspace(char src);

// ft_split.c //
int							delimiter(char *s, char c);
int							n_array(char *s, char c);
char						**junction_strs(char *s, char c, int i);
char						**ft_split(char const *s, char c);

#endif