/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ren_cone_side.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:03:02 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:03:03 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/*
m = tan^2, coefficient of the slope expansion
m . (ocn^2 + 2 . t . ocn . dn + t^2 . dn^2)
*/
static t_cy_quad	co_quad_init(t_ray *ray, t_cylinder *co, t_vec axis)
{
	t_cy_quad	q;
	double		dn;
	double		ocn;
	double		m;

	q.r = co->diameter;
	m = (q.r * q.r) / (co->height * co->height);
	q.oc = sub_vec(ray->origin, co->center);
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
	t_cy_quad q;
	double t;

	q = co_quad_init(ray, co, axis);
	if (q.disc < EPSILON)
		return (0);
	q.sd = sqrt(q.disc);
	q.t1 = (-q.b - q.sd) / (2.0 * q.a);
	q.t2 = (-q.b + q.sd) / (2.0 * q.a);
	t = smallest_positive_within_co(ray, co, axis, q);
	if (t < EPSILON)
		return (0);
	*t_side = t;
	return (1);
}