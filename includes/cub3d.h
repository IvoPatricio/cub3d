#ifndef  CUB3D_H
# define CUB3D_H
# define BUFFER_SIZE 1
// GAME SETTINGS //
# define WINDOW_X 800
# define WINDOW_Y 600
# define ROTATE_SPEED 0.2
# define PLAYER_SPEED 2

# define PI 3.141592653589
# define P2 PI/2
# define P3 3*PI/2
# define RGB_RED 0xFF0000
# define RGB_WHITE 0xFFFFFF
# define RGB_BLACK 0x000000
# define RGB_YELLOW 0xFFFF00
# define DR 0.01745329
# define WALL '1'
# define FLOOR '0'
# define SPACE ' '
# define NORTH 'N'
# define EAST 'E'
# define WEST 'W'
# define SOUTH 'S'

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

# include "../srcs/parse/get_next_line/get_next_line.h"
# include "../mini-linux/mlx.h"

typedef struct s_data	t_data;
typedef struct s_map	t_map;

typedef struct s_map
{
	void	*mlx;
	void	*win;
	void	*wall;
	void	*enemy;
	void	*player;
	void	*black;
	char	**map;
	int		y;
	int		x;
	float	pixels_y;
	float	pixels_x;
	float	diff_x;
	float	diff_y;
	float	angle;

	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	void	*img_floor1;
	void	*img_roof1;
	char	*addr1;
	char	*addr2;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	//t_texturedir
	//t_character
	t_data 	*data;
}			t_map;

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
}			t_data;

typedef struct s_texturedir
{
	char			*n;
	char			*s;
	char			*w;
	char			*e;
	int				roof;
	int				floor;
}			t_texturedir;

typedef struct s_character
{
	double	position_x;
	double	position_y;
	double	direction_x;
	double	direction_y;
}				t_character;

// PARSE FUNCTION //
// init.c //

void		init(t_data *data, t_texturedir *texture);
void		init_texturedir(t_data *data, t_texturedir *texture);
int			create_trgb(int t, int r, int g, int b);
int			map_rgb(t_data *data, t_texturedir *texture);

// ft_split.c //
static int	n_palavras(char *s, char c, int i);
int			delimiter(char *s, char c);
int			n_array(char *s, char c);
char		**junction_strs(char *s, char c, int i);
char		**ft_split(char const *s, char c);

// free_utils.c //
void		free_map(t_data *data);
void		free_rest(t_data *data);

// printf_utils.c //
void		printf_error(t_data *data, const char *str);
void		printf_map(t_data *data);
void		printf_paths(t_data *data);

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