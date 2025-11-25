#include "../include/minirt.h"

void ft_err(char *str, t_collector **g_root)
{
    ft_printf("Error: %s\n", str);
    gc_free_all(g_root);
    exit(1);
}

int invalid_file(int argc, char **argv, int *fd, t_collector **g_root)
{
    int len;
    if (argc != 2)
        return (1);
    len = ft_strlen(argv[1]);
    if (len < 3)
        return (1);
    if (argv[1][len - 3] != '.' ||
        argv[1][len - 2] != 'r' ||
        argv[1][len - 1] != 't')
        return (1);
    *fd = open(argv[1], O_RDONLY);
    if (*fd == -1)
        ft_err("failed to read the file", g_root);
    return (0);
}