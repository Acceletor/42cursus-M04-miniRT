#include "../include/minirt.h"

static int	intersect_cap(t_capq *q, double *t_hit)
{
	double	den;
	double	t;
	t_vec	p;
	t_vec	v;

	den = dot_vec(q->ray->dir, q->normal);
	if (fabs(den) < EPSILON)
		return (0);
	t = dot_vec(sub_vec(q->center, q->ray->origin), q->normal) / den;
	if (t <= EPSILON)
		return (0);
	p = add_vec(q->ray->origin, mult_vec(q->ray->dir, t));
	v = sub_vec(p, q->center);
	if (dot_vec(v, v) > q->r * q->r)
		return (0);
	*t_hit = t;
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