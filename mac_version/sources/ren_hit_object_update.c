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

// t_inter hit_cylinder_update(t_inter best, t_objs *obj, t_ray *ray)
// {
//     t_inter hit;
//     t_cylinder *cy;
//     double t;
//     int part;
//     t_vec axis;
//     t_vec v;

//     cy = (t_cylinder *)obj->data;
//     if (!cylinder_intersection_closed(ray, cy, &t, &part))
//         return (best);
//     if (best.t > 0.0 && t >= best.t)
//         return (best);
//     axis = vec_normalize(cy->normal);
//     hit = best;
//     hit.t = t;
//     hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
//     hit.color = cy->color;
//     if (part == 0) //side
//     {
//         v = sub_vec(hit.hit, cy->center);
//         hit.norm = vec_normalize(sub_vec(v, mult_vec(axis, dot_vec(v, axis))));
//     }
//     else if (part == 1) // top cap
//         hit.norm = axis;
//     else
//         hit.norm = mult_vec(axis, -1); //bottom cap

//     if (dot_vec(hit.norm, ray->dir) > 0.0)
//         hit.norm = mult_vec(hit.norm, -1.0);
//     return (hit);
// }

static t_vec	cy_part_normal(t_cylinder *cy, t_vec axis, t_vec hit, int part)
{
    t_vec	v;
	double	proj;

	if (part == 0)
	{
        v = sub_vec(hit, cy->center);
	    proj = dot_vec(v, axis);
	    return (vec_normalize(sub_vec(v, mult_vec(axis, proj))));
    }
	if (part == 1)
		return (axis);
	return (mult_vec(axis, -1.0));
}

t_inter hit_cylinder_update(t_inter best, t_objs *obj, t_ray *ray)
{
    t_inter hit;
    t_cylinder *cy;
    double t;
    int part;
    t_vec axis;

    cy = (t_cylinder *)obj->data;
    if (!cylinder_intersection_closed(ray, cy, &t, &part))
        return (best);
    if (best.t > 0.0 && t >= best.t)
        return (best);
    axis = vec_normalize(cy->normal);
    hit = best;
    hit.t = t;
    hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
    hit.color = cy->color;
    hit.norm = cy_part_normal(cy, axis, hit.hit, part);
    if (dot_vec(hit.norm, ray->dir) > 0.0)
        hit.norm = mult_vec(hit.norm, -1.0);
    return (hit);
}
