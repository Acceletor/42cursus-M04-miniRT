#include "../include/minirt.h"

void init_scene(t_data *data)
{
    data->scene.objs = NULL;
    data->scene.light = NULL;
    data->scene.amb.is_set = false;
    data->scene.amb.ratio = 0.0;
    data->scene.cam.is_set = false;

}