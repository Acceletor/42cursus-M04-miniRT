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

int sphere_intersect(t_ray *ray, t_sphere *sp ,double *t_hit)
{
    t_sp_tmp sph;
    double t;

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

// int plane_intersection(t_ray *ray, )