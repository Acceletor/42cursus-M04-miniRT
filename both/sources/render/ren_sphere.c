#include "../include/minirt.h"

/*
https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html

Equation of a sphere, points are on the sphere if center_distance == radius.
∣ P - C ∣^2 = r^2
...
(at^2 + bt + c ) calculating parts of the quadric equation
disc - discriminant (in polish 'delta')
if < 0 - no hits.
if == 0 - 1 hit
if > 0 - 2 hits

calculating the solutions of the quadric equation.
getting the closer one.
*/
static int	sphere_intersect(t_ray *ray, t_sphere *sp, double *t_hit)
{
	t_sp_quad	q;
	double		t;

	q.r = sp->diameter * 0.5;
	q.oc = sub_vec(ray->origin, sp->center);
	q.a = dot_vec(ray->dir, ray->dir);
	q.b = 2.0 * dot_vec(ray->dir, q.oc);
	q.c = dot_vec(q.oc, q.oc) - (q.r * q.r);
	q.disc = (q.b * q.b) - (4.0 * q.a * q.c);
	if (q.disc < 0.0)
		return (0);
	q.sd = sqrt(q.disc);
	q.t1 = (-q.b - q.sd) / (2.0 * q.a);
	q.t2 = (-q.b + q.sd) / (2.0 * q.a);
	t = smallest_positive(q.t1, q.t2);
	if (t < 0.0)
		return (0);
	*t_hit = t;
	return (1);
}

t_inter	hit_sphere_update(t_inter best, t_objs *obj, t_ray *ray)
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
	if (dot_vec(hit.norm, ray->dir) > 0.0)
		hit.norm = vec_normalize(mult_vec(hit.norm, -1.0));
	hit.color = sp->color;
	return (hit);
}