# include "./mini-linux/mlx.h"
#include <stdio.h>

int is_movement_active = 0;

typedef struct s_data
{
            void *mlx;
            void *mlx_win;
}               t_data;

int key_press_hook(int keycode, void *param)
{
    if (keycode == 119) // 'w' key pressed
    {
        is_movement_active = 1;
    }
    if (keycode == 100)
    {
        is_movement_active = 2;
    }

    return 0;
}

int key_release_hook(int keycode, void *param)
{
    if (keycode == 119) // 'w' key released
    {
        is_movement_active = 0;
    }
    if (keycode == 100)
    {
        is_movement_active = 0;
    }

    return 0;
}

void update_movement(t_data *data)
{
    static float w;
    static float d;

    if (is_movement_active == 1)
    {
            mlx_pixel_put(data->mlx, data->mlx_win, 100 + w , 100 + d, 0xFFFFFF);
            w = w + 0.001;
            printf("%f\n", w);
            printf("Moving forward...\n");
    }
    if (is_movement_active == 2)
    {
            mlx_pixel_put(data->mlx, data->mlx_win, 100 + w , 100 + d, 0xFFFFFF);
            d = d + 0.001;
            printf("%f\n", d);
            printf("Moving forward...\n");
    }
}

int main()
{
    t_data data;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 800, 800, "Hello world!");
    mlx_hook(data.mlx_win, 2, 1L<<0, key_press_hook, NULL);
    mlx_hook(data.mlx_win, 3, 1L<<1, key_release_hook, NULL);
    mlx_loop_hook(data.mlx, update_movement, &data);

    mlx_loop(data.mlx);

    return 0;
}
