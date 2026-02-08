#include "../include/minirt.h"

static int	cy_pick_best(t_cy_hits h, double *t_best, int *part)
{
	*t_best = -1.0;
	*part = -1;
	if (h.t_side > EPSILON && (*t_best < 0.0 || h.t_side < *t_best))
		(*t_best = h.t_side, *part = 0);
	if (h.t_top > EPSILON && (*t_best < 0.0 || h.t_top < *t_best))
		(*t_best = h.t_top, *part = 1);
	if (h.t_bot > EPSILON && (*t_best < 0.0 || h.t_bot < *t_best))
		(*t_best = h.t_bot, *part = 2);
	return (*t_best > 0.0);
}

/* calculates the centers of the top and bottom cap */
static void cy_caps_init(t_circle *top, t_circle *bot, t_cylinder *cy, t_vec axis)
{
  top->diameter = cy->diameter;
  top->center = add_vec(cy->center, mult_vec(axis, cy->height * 0.5));
  top->normal = axis;

  bot->diameter = cy->diameter;
  bot->center = sub_vec(cy->center, mult_vec(axis, cy->height * 0.5));
  bot->normal = mult_vec(axis, -1.0);
}

/* 
Composite object
The Side (Finite Cylider)
Bottom and top cap
*/
static int	cylinder_intersection_closed(t_ray *ray, t_cylinder *cy, double *t_hit,
		int *part)
{
  t_circle	top;
  t_circle	bot;
  t_vec axis;
	t_cy_hits	h;
	double		t_best;

	h.t_side = -1.0;
	h.t_top = -1.0;
	h.t_bot = -1.0;
  axis = vec_normalize(cy->normal);
	cy_caps_init(&top, &bot, cy, axis);
	cy_side_hit(ray, cy, axis, &h.t_side);
	circle_inersection(ray, &top, &h.t_top);
  circle_inersection(ray, &bot, &h.t_bot);
	if (!cy_pick_best(h, &t_best, part))
		return (0);
	*t_hit = t_best;
	return (1);
}

static t_vec	cy_part_normal(t_cylinder *cy, t_vec axis, t_vec hit, int part)
{
	t_vec	v;
	double	proj;

	if (part == 0)
	{
		v = sub_vec(hit, cy->center);
		proj = dot_vec(v, axis);
		return (vec_normalize(sub_vec(v, mult_vec(axis, proj))));
	}
	if (part == 1)
		return (axis);
  return (mult_vec(axis, -1.0));
}

t_inter	hit_cylinder_update(t_inter best, t_objs *obj, t_ray *ray)
{
	t_inter		hit;
	t_cylinder	*cy;
	double		t;
	int			part;
	t_vec		axis;

	cy = (t_cylinder *)obj->data;
	if (!cylinder_intersection_closed(ray, cy, &t, &part))
		return (best);
	if (best.t > 0.0 && t >= best.t)
		return (best);
	axis = vec_normalize(cy->normal);
	hit = best;
	hit.t = t;
	hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
	hit.color = cy->color;
	hit.norm = cy_part_normal(cy, axis, hit.hit, part);
	if (dot_vec(hit.norm, ray->dir) > 0.0)
		hit.norm = mult_vec(hit.norm, -1.0);
	return (hit);
}

/* Infinite cylinder */
t_inter	hit_tube_update(t_inter best, t_objs *obj, t_ray *ray)
{
  t_inter		hit;
	t_cylinder	*cy;
	double		t;
	t_vec		axis;

	cy = (t_cylinder *)obj->data;
  axis = vec_normalize(cy->normal);
  if(!cy_infinite_hit(ray, cy, axis, &t))
		return (best);
	if (best.t > 0.0 && t >= best.t)
		return (best);
	hit = best;
	hit.t = t;
	hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
	hit.color = cy->color;
	hit.norm = cy_part_normal(cy, axis, hit.hit, 0);
	if (dot_vec(hit.norm, ray->dir) > 0.0)
		hit.norm = mult_vec(hit.norm, -1.0);
	return (hit);
}

// t_inter hit_cylinder_update(t_inter best, t_objs *obj, t_ray *ray)
// {
//     t_inter hit;
//     t_cylinder *cy;
//     double t;
//     int part;
//     t_vec axis;
//     t_vec v;

//     cy = (t_cylinder *)obj->data;
//     if (!cylinder_intersection_closed(ray, cy, &t, &part))
//         return (best);
//     if (best.t > 0.0 && t >= best.t)
//         return (best);
//     axis = vec_normalize(cy->normal);
//     hit = best;
//     hit.t = t;
//     hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
//     hit.color = cy->color;
//     if (part == 0) //side
//     {
//         v = sub_vec(hit.hit, cy->center);
//         hit.norm = vec_normalize(sub_vec(v, mult_vec(axis, dot_vec(v,
					// axis))));
//     }
//     else if (part == 1) // top cap
//         hit.norm = axis;
//     else
//         hit.norm = mult_vec(axis, -1); //bottom cap

//     if (dot_vec(hit.norm, ray->dir) > 0.0)
//         hit.norm = mult_vec(hit.norm, -1.0);
//     return (hit);
// }
