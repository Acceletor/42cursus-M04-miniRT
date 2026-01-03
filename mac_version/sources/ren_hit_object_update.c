#include "../include/minirt.h"

t_inter hit_sphere_update(t_inter best, t_objs *obj, t_ray *ray)
{
    t_inter hit;
    t_sphere *sp;
    double t;

    sp = (t_sphere *)obj->data;
    if (!sphere_intersect(ray, sp, &t))
        return (best);
    if (best.t > 0.0 && t >= best.t)
        return (best);
    hit = best;
    hit.t = t;
    hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
    hit.norm = vec_normalize(sub_vec(hit.hit, sp->center));
    hit.color = normalize_color(sp->color);

    return (hit);
}