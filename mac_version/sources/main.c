#include "../include/minirt.h"


// void my_mlx_pixel_put(t_image *img, int x, int y, int color)
// {
//     char *dst;
//     if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
//         return;
//     dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel/8));
//     *(unsigned int *)dst = (unsigned int)color;
// }


int main(int argc, char **argv)
{
    t_data data;

    data.gc_root = NULL;
    data.fd = -1;
    if (invalid_file(argc, argv, &data))
        ft_err("Incorrect argument: ./miniRT file_name.rt", &data.gc_root, 1);
    init_scene(&data);
    parse(&data);
    print_scene(&data);
    rendering(&data);

    // .......program logic.......
    
    gc_free_all(&data.gc_root);
    // close(fd)
    return 0;
}