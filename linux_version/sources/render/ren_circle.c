#include "../include/minirt.h"

/*
Plane logic
...
Calculate hit coords (p)
Calculate distance to center and compare with radius
*/
int	circle_intersection(t_ray *ray, t_circle *ci, double *t_hit)
{
	double	den;
	double	t;
	t_vec	p;
	t_vec	v;
  double r;

	den = dot_vec(ray->dir, ci->normal);
	if (fabs(den) < EPSILON)
		return (0);
	t = dot_vec(sub_vec(ci->center, ray->origin), ci->normal) / den;
	if (t <= EPSILON)
		return (0);
	p = add_vec(ray->origin, mult_vec(ray->dir, t));
	v = sub_vec(p, ci->center);
  r = ci->diameter * 0.5;
	if (dot_vec(v, v) > r * r)
		return (0);
	*t_hit = t;
	return (1);
}

t_inter	hit_circle_update(t_inter best, t_objs *obj, t_ray *ray)
{
	t_inter	hit;
	t_circle	*ci;
	double	t;

	ci = (t_circle *)obj->data;
	if (!circle_intersection(ray, ci, &t))
		return (best);
	if (best.t > 0.0 && t >= best.t)
		return (best);
	hit = best;
	hit.t = t;
	hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
	hit.norm = vec_normalize(ci->normal);
	if (dot_vec(hit.norm, ray->dir) > 0.0)
		hit.norm = vec_normalize(mult_vec(hit.norm, -1.0));
	hit.color = ci->color;
	return (hit);
}