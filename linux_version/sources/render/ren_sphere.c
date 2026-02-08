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

t_inter	hit_sphere_update(t_inter best, t_objs *obj, t_ray *ray)
{
	t_inter		hit;
	t_sphere	*sp;
	double		t;

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