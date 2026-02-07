#include "../include/minirt.h"

static int	plane_intersection(t_ray *ray, t_plane *pl, double *t_hit)
{
	double	demon;
	t_vec	p0_to_o;
	double	t;

	demon = dot_vec(ray->dir, pl->normal);
	if (fabs(demon) < EPSILON)
		return (0);
	p0_to_o = sub_vec(pl->point, ray->origin);
	t = dot_vec(p0_to_o, pl->normal) / demon;
	if (t < EPSILON)
		return (0);
	*t_hit = t;
	return (1);
}

t_inter	hit_plane_update(t_inter best, t_objs *obj, t_ray *ray)
{
	t_inter	hit;
	t_plane	*pl;
	double	t;

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