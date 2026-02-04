#include "../include/minirt.h"

void	ft_err(char *str, t_collector **g_root, int err)
{
	ft_printf("Error: %s\n", str);
	if (g_root && *g_root)
		gc_free_all(g_root);
	exit(err);
}
