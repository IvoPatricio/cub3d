#ifndef CUB3D_H
# define CUB3D_H
# define BUFFER_SIZE 1

// GAME SETTINGS //
# define WIN_X 800
# define WIN_Y 640
# define ROTATE_SPEED 0.2
# define PLAYER_SPEED 0.1

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

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<string.h>
# include<stdarg.h>
# include<sys/types.h>
# include<sys/stat.h>
# include<fcntl.h>
# include<limits.h>
# include<string.h>
# include<math.h>
# include<stdbool.h>

# include "../srcs/utils/get_next_line/get_next_line.h"
# include "../mini-linux/mlx.h"

typedef struct s_data		t_data;
typedef struct s_map		t_map;
typedef struct s_ray		t_ray;
typedef struct s_play		t_play;
typedef struct s_texture	t_texture;
typedef struct s_mlx		t_mlx;

typedef struct s_map
{
	char			**map;
	void			*aaa;
	t_play			*play;
	t_ray			*ray;
	t_texture 		*texture;
	t_data			*data;
	t_mlx			*mlx;
}			t_map;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_to_window;
	char			*buffer;
	int				i;
	int				a;
	int				b;
	int				c;
}			t_mlx;

typedef struct s_play
{
	double			posX;
	double			posY;
	double			dir_x;
	double			dir_y;
	double			old_dir_x;
	double			old_plane_x;
	double			plane_x;
	double			plane_y;
	t_map			*map;
}			t_play;

typedef struct s_ray
{
	double			cameraX;
	double			rayDirX;
	double			rayDirY;
	double			deltaDistX;
	double			deltaDistY;
	double			sideDistX;
	double			sideDistY;
	double			walldist;
	double			wallhit;
	double			step;
	int				mapX;
	int				mapY;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				line_height;
	int				drawstart;
	int				drawend;
}				t_ray;

typedef struct s_data
{
	char		**argv;
	int			arr;
	char		**map;
	char		*f;
	char		*c;
	char		**f_arr;
	char		**c_arr;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		direction;
	int			player_x;
	int			player_y;
}			t_data;

typedef struct s_texture
{
	char			*n;
	char			*s;
	char			*w;
	char			*e;
	char			player_direction;
	int				roof;
	int				floor;
}			t_texture;

typedef struct s_character
{
	double	position_x;
	double	position_y;
	double	direction_x;
	double	direction_y;
}				t_character;

// PARSE FUNCTION //
// init.c //

void		init_structs(t_map *map);
void		init_textured(t_data *data, t_texture *texture);
void 		init_player(t_data *data, t_play *play);
int			create_trgb(int t, int r, int g, int b);
void 		map_rgb(t_data *data, t_texture *texture);

// ft_split.c //
static int	n_palavras(char *s, char c, int i);
int			delimiter(char *s, char c);
int			n_array(char *s, char c);
char		**junction_strs(char *s, char c, int i);
char		**ft_split(char const *s, char c);

// free_utils.c //
void		free_map(t_data *data);
void		free_rest(t_data *data);
void		free_structs_mlx(t_map *map);
void		struct_malloc_error(t_map *map, const void *random, size_t size);
void		string_malloc_error(t_data *data, char *a);
void		array_malloc_error(t_data *data, char **a);

// printf_utils.c //
void		printf_error(t_data *data, const char *str);
void		printf_map(t_data *data);
void		printf_paths(t_data *data);
void		printf_struct_map(t_map *map);
void 		printf_struct_player(t_play *play);

// rgb_path_parse.c //
void 		rgb_path_parse1(t_data *data, char *b, int i);
void 		rgb_path_parse2(t_data *data);
void 		rgb_path_parse3(t_data *data);
char 		*give_mem_char(char *dest, char *src);

// main_parse.c //
void		main_parse(t_data *data);
void		map_boundaries(t_data *data);
void		map_check_char(t_data *data);
void		map_array(t_data *data);
void		map_array_strings(t_data *data);
void		arg_parse(t_data *data);

// parse_utils.c //
void		*ft_memset(void *b, int c, size_t len);
size_t		ft_lenspace(const char *str);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);

// utils //
//errors.c//

//int			print_error_and_return(char *message, int code);

#endif