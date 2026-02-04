#include "../include/minirt.h"

double	get_smallest_positive(double t1, double t2)
{
	if (t1 > EPSILON && t2 > EPSILON)
	{
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	if (t1 > EPSILON)
		return (t1);
	if (t2 > EPSILON)
		return (t2);
	return (-1.0);
}

int	sphere_intersect(t_ray *ray, t_sphere *sp, double *t_hit)
{
	t_sp_tmp	sph;
	double		t;

	sph.r = sp->diameter * 0.5;
	sph.oc = sub_vec(ray->origin, sp->center);
	sph.a = dot_vec(ray->dir, ray->dir);
	sph.b = 2.0 * dot_vec(ray->dir, sph.oc);
	sph.c = dot_vec(sph.oc, sph.oc) - (sph.r * sph.r);
	sph.disc = (sph.b * sph.b) - (4.0 * sph.a * sph.c);
	if (sph.disc < 0.0)
		return (0);
	sph.sqrt_disc = sqrt(sph.disc);
	sph.t1 = (-sph.b - sph.sqrt_disc) / (2.0 * sph.a);
	sph.t2 = (-sph.b + sph.sqrt_disc) / (2.0 * sph.a);
	t = get_smallest_positive(sph.t1, sph.t2);
	if (t < 0.0)
		return (0);
	*t_hit = t;
	return (1);
}

int	plane_intersection(t_ray *ray, t_plane *pl, double *t_hit)
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

int	cylinder_intersection_closed(t_ray *ray, t_cylinder *cy, double *t_hit,
		int *part)
{
	t_cy_caps	c;
	t_cy_hits	h;
	double		t_best;

	c = cy_caps_init(cy);
	h.t_side = -1.0;
	h.t_top = -1.0;
	h.t_bot = -1.0;
	cy_side_hit(ray, cy, c.axis, &h.t_side);
	cy_caps_hits(ray, c, &h);
	if (!cy_pick_best(h, &t_best, part))
		return (0);
	*t_hit = t_best;
	return (1);
}

int	intersect_cap(t_capq *q, double *t_hit)
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
