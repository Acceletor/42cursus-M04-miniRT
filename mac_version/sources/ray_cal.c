#include "../include/minirt.h"

t_inter scene_inter(t_ray *ray, t_scene *sc)
{
    t_inter best;
    t_objs *obj;

    best.t = -1.0;
    best.hit = (t_vec){0,0,0};
    best.norm = (t_vec){0,0,0};
    best.color = (t_vec){0,0,0};
    obj = sc->objs;
    while(obj)
    {
        if (obj->type == OBJ_SPHERE)
            best = hit_sphere_update(best, obj, ray);
        // else if (obj->type == OBJ_PLANE)
        //     hold = plane_normal();
        // else if (obj->type == OBJ_CYLINDER)
        //     hold = cylinder_normal();
        obj = obj->next;
    }
    return (best);
}

t_vec   ray_color(t_ray *ray, t_scene *sc)
{
    t_inter inter;
    // t_vec px_col;
    // t_vec amb;
    
    inter = scene_inter(ray, sc);
    if (inter.t > EPSILON)
    {
        // compute amb + light;
        return (inter.color); //HIT
    }
    return (normalize_color(mult_vec(sc->amb.color, sc->amb.ratio)));
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