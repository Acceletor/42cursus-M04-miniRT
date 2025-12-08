#include "../include/minirt.h"

int allocate_scene(t_data *data)
{
    data->scene = gc_malloc(&data->gc_root, sizeof(t_scene));
    if (!data->scene)
        return (0);
    (data->scene)->objs = NULL;
    (data->scene)->light = NULL;
    (data->scene)->amb.is_set = false;
    (data->scene)->cam.is_set = false;
    return (1);
}