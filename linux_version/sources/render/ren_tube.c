/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ren_tube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:18:15 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:18:18 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* cylinder without caps */
t_inter	hit_tube_update(t_inter best, t_objs *obj, t_ray *ray)
{
	t_inter		hit;
	t_cylinder	*cy;
	double		t;
	t_vec		axis;

	cy = (t_cylinder *)obj->data;
	axis = cy->normal;
	if (!cy_infinite_hit(ray, cy, axis, &t))
		return (best);
	if (best.t > EPSILON && t >= best.t)
		return (best);
	hit = best;
	hit.t = t;
	hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
	hit.color = cy->color;
	hit.norm = cy_part_normal(cy, axis, hit.hit, 0);
	if (dot_vec(hit.norm, ray->dir) > EPSILON)
		hit.norm = mult_vec(hit.norm, -1.0);
	return (hit);
}
