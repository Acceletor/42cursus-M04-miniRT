/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ren_cylinder_side.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:03:06 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:03:07 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/*
Calculates the perpendicular to axis components, transition to a 2d plane
dir -> d_perp - perpendicular component of dir
oc -> oc_prep - perpendicular component of oc
then sphere calculations
*/
static t_cy_quad	cy_quad_init(t_ray *ray, t_cylinder *cy, t_vec axis)
{
	t_cy_quad	q;
	double		dn;
	double		ocn;

	q.oc = sub_vec(ray->origin, cy->center);
	dn = dot_vec(ray->dir, axis);
	ocn = dot_vec(q.oc, axis);
	q.d_perp = sub_vec(ray->dir, mult_vec(axis, dn));
	q.oc_perp = sub_vec(q.oc, mult_vec(axis, ocn));
	q.r = cy->diameter * 0.5;
	q.a = dot_vec(q.d_perp, q.d_perp);
	q.b = 2.0 * dot_vec(q.oc_perp, q.d_perp);
	q.c = dot_vec(q.oc_perp, q.oc_perp) - q.r * q.r;
	q.disc = q.b * q.b - 4.0 * q.a * q.c;
	return (q);
}

/*
Checks the height - calculate the hit point, compare it's height
*/
int	cy_side_hit(t_ray *ray, t_cylinder *cy, t_vec axis, double *t_side)
{
	t_cy_quad	q;
	double		t;
	t_vec		p;
	double		y;

	q = cy_quad_init(ray, cy, axis);
	if (fabs(q.a) < EPSILON || q.disc < EPSILON)
		return (0);
	q.sd = sqrt(q.disc);
	q.t1 = (-q.b - q.sd) / (2.0 * q.a);
	q.t2 = (-q.b + q.sd) / (2.0 * q.a);
	t = smallest_positive(q.t1, q.t2);
	if (t < EPSILON)
		return (0);
	p = add_vec(ray->origin, mult_vec(ray->dir, t));
	y = dot_vec(sub_vec(p, cy->center), axis);
	if (fabs(y) > cy->height * 0.5)
		return (0);
	*t_side = t;
	return (1);
}

int	cy_infinite_hit(t_ray *ray, t_cylinder *cy, t_vec axis, double *t_side)
{
	t_cy_quad	q;
	double		t;

	q = cy_quad_init(ray, cy, axis);
	if (fabs(q.a) < EPSILON || q.disc < EPSILON)
		return (0);
	q.sd = sqrt(q.disc);
	q.t1 = (-q.b - q.sd) / (2.0 * q.a);
	q.t2 = (-q.b + q.sd) / (2.0 * q.a);
	if (cy->height)
		t = smallest_positive_within_cy(ray, cy, axis, q);
	else
		t = smallest_positive(q.t1, q.t2);
	if (t < EPSILON)
		return (0);
	*t_side = t;
	return (1);
}
