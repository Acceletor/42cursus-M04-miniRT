#include "../include/minirt.h"

t_inter find_inter(t_ray *ray, t_scene *sc)
{
    t_inter hold;
    t_objs *obj;

    hold.t = -1.0;
    obj = sc->objs;
    while(obj)
    {
        if (obj->type == OBJ_SPHERE)
            hold = sphere_normal();
        // else if (obj->type == OBJ_PLANE)
        //     hold = plane_normal();
        // else if (obj->type == OBJ_CYLINDER)
        //     hold = cylinder_normal();
        obj = obj->next;
    }
    return hold;
}


t_vec   ray_color(t_ray *ray, t_scene *sc)
{
    t_inter inter;
    t_vec px_col;
    t_vec amb;
    
}

t_ray ray_primary(t_camera *cam, double sx, double sy)
{
    t_ray ray;
    double horizontal_offset;
    double vertical_offset;

    horizontal_offset = sx * (cam->vp_width * 0.5);
    vertical_offset = sy * (cam->vp_height * 0.5);

    ray.origin = cam->pos;
    ray.dir = add_vec(cam->forward,
                add_vec(
                    mult_vec(cam->right, horizontal_offset), 
                    mult_vec(cam->up, vertical_offset)
                ));
    ray.dir = vec_normalize(ray.dir);
    return (ray);
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
            info->ray_col = ray_color()
            info->x++;
        }
        info->y++;
    }
}

void rendering(t_scene *sc)
{
    t_renderer info;

    info.cam = set_camera(sc);
    image_init(&info);
    draw(&info, sc);
    
}