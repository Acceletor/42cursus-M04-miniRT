/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ren_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:03:18 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:09:09 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	smallest_positive(double t1, double t2)
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

static int	is_within_cylinder(t_ray *ray, t_cylinder *cy, t_vec axis, double t)
{
	t_vec	p;
	double	y;

	p = add_vec(ray->origin, mult_vec(ray->dir, t));
	y = dot_vec(sub_vec(p, cy->center), axis);
	if (fabs(y) > cy->height * 0.5)
		return (0);
	return (1);
}

static int	is_within_cone(t_ray *ray, t_cylinder *cy, t_vec axis, double t)
{
	t_vec	hit;
	t_vec	top;
	double	h;

	top = add_vec(cy->center, mult_vec(axis, cy->height * 0.5));
	hit = add_vec(ray->origin, mult_vec(ray->dir, t));
	h = dot_vec(sub_vec(hit, top), axis);
	if (h < EPSILON && h > -cy->height)
		return (1);
	return (0);
}

double	smallest_positive_within_co(t_ray *ray, t_cylinder *co, t_vec axis,
		t_cy_quad q)
{
	if (q.t1 > EPSILON && is_within_cone(ray, co, axis, q.t1))
	{
		if (q.t2 > EPSILON && is_within_cone(ray, co, axis, q.t2))
		{
			if (q.t1 < q.t2)
				return (q.t1);
		}
		return (q.t1);
	}
	else if (q.t2 > EPSILON && is_within_cone(ray, co, axis, q.t2))
	{
		return (q.t2);
	}
	return (-1.0);
}

double	smallest_positive_within_cy(t_ray *ray, t_cylinder *cy, t_vec axis,
		t_cy_quad q)
{
	if (q.t1 > EPSILON && is_within_cylinder(ray, cy, axis, q.t1))
	{
		if (q.t2 > EPSILON && is_within_cylinder(ray, cy, axis, q.t2))
		{
			if (q.t1 < q.t2)
				return (q.t1);
		}
		return (q.t1);
	}
	else if (q.t2 > EPSILON && is_within_cylinder(ray, cy, axis, q.t2))
	{
		return (q.t2);
	}
	return (-1.0);
}
