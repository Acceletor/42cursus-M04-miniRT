#include "../include/minirt.h"

static t_cy_quad	co_quad_init(t_ray *ray, t_cylinder *co, t_vec axis)
{
	t_cy_quad	q;
	double		dn;
	double		ocn;
  double m;

  t_vec top = co->center;
  q.r = co->diameter;
  m = (q.r * q.r) / (co->height * co->height);
	q.oc = sub_vec(ray->origin, top);
	dn = dot_vec(ray->dir, axis);
	ocn = dot_vec(q.oc, axis);
	q.d_perp = sub_vec(ray->dir, mult_vec(axis, dn));
	q.oc_perp = sub_vec(q.oc, mult_vec(axis, ocn));
	q.a = dot_vec(q.d_perp, q.d_perp) - (m * dn * dn);
	q.b = 2.0 * (dot_vec(q.oc_perp, q.d_perp) - (m * ocn * dn));
	q.c = dot_vec(q.oc_perp, q.oc_perp) - (m * ocn * ocn);
	q.disc = q.b * q.b - 4.0 * q.a * q.c;
	return (q);
}


int	co_side_hit(t_ray *ray, t_cylinder *co, t_vec axis, double *t_side)
{
  t_cy_quad	q;
  double t;

	q = co_quad_init(ray, co, axis);
	if (q.disc < 0.0)
		return (0);
	q.sd = sqrt(q.disc);
	q.t1 = (-q.b - q.sd) / (2.0 * q.a);
	q.t2 = (-q.b + q.sd) / (2.0 * q.a);
	t = smallest_positive_within_co(ray, co, axis, q);
  if (t < 0.0) 
    return (0);
  *t_side = t;
	return (1);
}