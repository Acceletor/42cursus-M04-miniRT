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

int plane_intersection(t_ray *ray, t_plane *pl, double *t_hit)
{
	double demon;
	t_vec p0_to_o;
	double t;

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

int cylinder_intersection(t_ray *ray, t_cylinder *cy, double *t_hit)
{
	t_cy_tmp cyl;
	double t;

	cyl.oc = sub_vec(ray->origin, cy->center);
	cyl.d_dot_n = dot_vec(ray->dir, cy->normal);
	cyl.d_side = sub_vec(ray->dir ,mult_vec(cy->normal, cyl.d_dot_n));
	cyl.oc_dot_n = dot_vec(cyl.oc, cy->normal);
	cyl.oc_side = sub_vec(cyl.oc, mult_vec(cy->normal, cyl.oc_dot_n));
	cyl.r = cy->diameter/2;
	cyl.a = dot_vec(cyl.d_side, cyl.d_side); 
	if (fabs(cyl.a) < EPSILON)
		return (0);
	cyl.b = 2.0 * dot_vec(cyl.oc_side, cyl.d_side);
	cyl.c = dot_vec(cyl.oc_side, cyl.oc_side) - (cyl.r) * (cyl.r);
	cyl.disc = cyl.b * cyl.b - 4.0 * cyl.a * cyl.c;
	if (cyl.disc < 0.0)
		return (0);
	cyl.sqrt_disc = sqrt(cyl.disc);
	cyl.t1 = (-cyl.b - cyl.sqrt_disc) / (2.0 * cyl.a);
	cyl.t2 = (-cyl.b + cyl.sqrt_disc) / (2.0 * cyl.a);
	t = get_smallest_positive(cyl.t1, cyl.t2);
	if (t < 0.0)
		return (0);
	cyl.P = add_vec(ray->origin, mult_vec(ray->dir, t));
	cyl.y = dot_vec(sub_vec(cyl.P, cy->center), cy->normal);
	if (fabs(cyl.y) > cy->height * 0.5)
		return (0);
	*t_hit = t;
	return (1);
}
