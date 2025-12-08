#include "../include/minirt.h"

void ft_err(char *str, t_collector **g_root)
{
    ft_printf("Error: %s\n", str);
    if (g_root != NULL)
        gc_free_all(g_root);
    exit(1);
}
