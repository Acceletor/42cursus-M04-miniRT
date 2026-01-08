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
    hit.color = sp->color;
    return (hit);
}

t_inter hit_plane_update(t_inter best, t_objs *obj, t_ray *ray)
{
    t_inter hit;
    t_plane *pl;
    double t;

    pl = (t_plane *)obj->data;
    if (!plane_intersection(ray, pl, &t))
        return (best);
    if (best.t > 0.0 && t >= best.t)
        return (best);
    hit = best;
    hit.t = t;
    hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
    hit.norm = vec_normalize(pl->normal);
    if (dot_vec(hit.norm, ray->dir) > 0.0)
        hit.norm = vec_normalize(mult_vec(hit.norm, -1.0));
    hit.color = pl->color;
    return (hit);
}
