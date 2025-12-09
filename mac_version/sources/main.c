#include "../include/minirt.h"

int main(int argc, char **argv)
{
    t_data data;

    data.gc_root = NULL;
    data.fd = -1;
    if (invalid_file(argc, argv, &data))
        ft_err("Incorrect argument: ./miniRT file_name.rt", &data.gc_root);
    init_scene(&data);
    parse(&data);
    printf("%f\n", data.scene.amb.ratio);
    // .......program logic.......
    
    gc_free_all(&data.gc_root);
    // close(fd)
    return 0;
}