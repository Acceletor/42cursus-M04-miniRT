#include "../include/minirt.h"

int allocate_scene(t_scene **sc, t_collector **g_root)
{
    *sc = gc_malloc(g_root, sizeof(t_scene));
    if (!*sc)
        return (0);
    (*sc)->objs = NULL;
    (*sc)->light = NULL;
    (*sc)->amb.is_set = false;
    (*sc)->cam.is_set = false;
    return (1);
}