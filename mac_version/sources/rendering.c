#include "../include/minirt.h"


void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel/8));
    *(unsigned int *)dst = (unsigned int)color;
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

void rendering(t_scene *sc)
{
    t_renderer info;

    info.cam = set_camera(sc);
    image_init(&info);
    draw(&info, sc);
    mlx_loop(info.mlx.mlx);
}
