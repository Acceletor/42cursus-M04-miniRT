#include "../include/minirt.h"

int	cy_pick_best(t_cy_hits h, double *t_best, int *part)
{
	*t_best = -1.0;
	*part = -1;
	if (h.t_side > EPSILON && (*t_best < 0.0 || h.t_side < *t_best))
		(*t_best = h.t_side, *part = 0);
	if (h.t_top > EPSILON && (*t_best < 0.0 || h.t_top < *t_best))
		(*t_best = h.t_top, *part = 1);
	if (h.t_bot > EPSILON && (*t_best < 0.0 || h.t_bot < *t_best))
		(*t_best = h.t_bot, *part = 2);
	return (*t_best > 0.0);
}

t_cy_caps	cy_caps_init(t_cylinder *cy)
{
	t_cy_caps	c;

	c.axis = vec_normalize(cy->normal);
	c.r = cy->diameter * 0.5;
	c.top = add_vec(cy->center, mult_vec(c.axis, cy->height * 0.5));
	c.bot = sub_vec(cy->center, mult_vec(c.axis, cy->height * 0.5));
	return (c);
}

t_cy_quad	cy_quad_init(t_ray *ray, t_cylinder *cy, t_vec axis)
{
	t_cy_quad	q;
	double		dn;
	double		on;

	q.oc = sub_vec(ray->origin, cy->center);
	dn = dot_vec(ray->dir, axis);
	on = dot_vec(q.oc, axis);
	q.d_perp = sub_vec(ray->dir, mult_vec(axis, dn));
	q.oc_perp = sub_vec(q.oc, mult_vec(axis, on));
	q.r = cy->diameter * 0.5;
	q.a = dot_vec(q.d_perp, q.d_perp);
	q.b = 2.0 * dot_vec(q.oc_perp, q.d_perp);
	q.c = dot_vec(q.oc_perp, q.oc_perp) - q.r * q.r;
	q.disc = q.b * q.b - 4.0 * q.a * q.c;
	return (q);
}

int	cy_side_hit(t_ray *ray, t_cylinder *cy, t_vec axis, double *t_side)
{
	t_cy_quad	q;
	double		sd;
	double		t;
	t_vec		p;
	double		y;

	q = cy_quad_init(ray, cy, axis);
	if (fabs(q.a) < EPSILON || q.disc < 0.0)
		return (0);
	sd = sqrt(q.disc);
	t = get_smallest_positive((-q.b - sd) / (2.0 * q.a), (-q.b + sd) / (2.0
				* q.a));
	if (t < 0.0)
		return (0);
	p = add_vec(ray->origin, mult_vec(ray->dir, t));
	y = dot_vec(sub_vec(p, cy->center), axis);
	if (fabs(y) > cy->height * 0.5)
		return (0);
	*t_side = t;
	return (1);
}

void	cy_caps_hits(t_ray *ray, t_cy_caps c, t_cy_hits *h)
{
	t_capq	q;

	q.ray = ray;
	q.r = c.r;
	q.center = c.top;
	q.normal = c.axis;
	intersect_cap(&q, &h->t_top);
	q.center = c.bot;
	q.normal = mult_vec(c.axis, -1.0);
	intersect_cap(&q, &h->t_bot);
}
