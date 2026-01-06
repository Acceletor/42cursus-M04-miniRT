#include "../include/minirt.h"

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel/8));
    *(unsigned int *)dst = (unsigned int)color;
}

// int handle_key(int keycode, void *param)
// {
//     t_data *data;

//     data = (t_data *)param;
//     if (keycode == 53)
//     {
//         mlx_destroy_window(data->renderer.mlx.mlx, data->renderer.mlx.win);
//         gc_free_all(&data->gc_root);
//         if (data->fd != -1)
//             close(data->fd);
//         exit(0);
//     }
//     return (0);
// }

int handle_key(int keycode, t_mlx *var) 
{ 
    if (keycode == 53)
    { 
        mlx_destroy_window(var->mlx, var->win);
        exit(0);
    }
    return (0); 
}

void draw(t_renderer *info, t_scene *sc)
{  
    info->y = 0;
    while (info->y < HEIGHT)
    {
        info->x = 0;
        while (info->x < WIDTH)
        {
            info->sx = ((info->x + 0.5)/ (double)WIDTH) * 2.0 - 1.0;
            info->sy = 1.0 - ((info->y + 0.5)/ (double)HEIGHT) * 2.0;
            info->ray = ray_primary(&info->cam, info->sx, info->sy);
            info->ray_col = ray_color(&info->ray, sc);
            my_mlx_pixel_put(&info->img, info->x, info->y,
                vec_to_rgb(info->ray_col));
            info->x++;
        }
        info->y++;
    }
    mlx_put_image_to_window(info->mlx.mlx, info->mlx.win, info->img.img, 0, 0);
}

// void rendering(t_data *data)
// {
//     t_renderer *info;

//     info = &data->renderer;
//     info->cam = set_camera(&data->scene);
//     image_init(info);
//     draw(info, &data->scene);
//     mlx_key_hook(info->mlx.win, handle_key, data);
//     mlx_loop(info->mlx.mlx);
// }

void rendering(t_scene *sc) 
{ 
    t_renderer info;
    
    info.cam = set_camera(sc);
    image_init(&info); draw(&info, sc);
    mlx_key_hook(info.mlx.win, handle_key, &info.mlx);
    mlx_loop(info.mlx.mlx); 
}