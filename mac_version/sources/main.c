#include "../include/minirt.h"

int main(int argc, char **argv)
{
    t_scene *sc;
    t_collector *g_root;
    int fd;

    g_root = NULL;
    if (invalid_file(argc, argv, &fd, &g_root))
        ft_err("Incorrect argument: ./miniRT file_name.rt", &g_root);
    if (!allocate_scene(&sc, &g_root))
        ft_err("allocation", &g_root);
    // .......program logic.......
    gc_free_all(&g_root);
    // close(fd)

    return 0;
}