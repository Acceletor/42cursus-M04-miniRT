#include "../include/minirt.h"

/*
Plane logic
...
Calculate hit coords (p)

*/
int	circle_inersection(t_ray *ray, t_circle *ci, double *t_hit)
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