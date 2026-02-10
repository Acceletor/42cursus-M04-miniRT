#include "../include/minirt.h"

static int	cone_intersection(t_ray *ray, t_cylinder *co, double *t_hit,
		int *part)
{
	t_circle	bot;
	t_circle	top;
	t_vec		axis;
	t_cy_hits	h;
	double		t_best;

	h.t_side = -1.0;
	h.t_bot = -1.0;
	h.t_top = -1.0;
	axis = vec_normalize(co->normal);
	cy_caps_init(&top, &bot, co, axis);
	co_side_hit(ray, co, axis, &h.t_side);
	circle_intersection(ray, &bot, &h.t_bot);
	circle_intersection(ray, &top, &h.t_top);
	if (!cy_pick_best(h, &t_best, part))
		return (0);
	*t_hit = t_best;
	return (1);
}

/* 
vector from center to hit
proj - distance along the axis
m cone coefficient
1 - x = -m
*/
static t_vec	co_part_normal(t_cylinder *co, t_vec axis, t_vec hit, int part)
{
	t_vec	hc;
	double	m;
	double	proj;

	if (part == 0)
	{
    hc = sub_vec(hit, co->center);
    proj = dot_vec(hc, axis);
    m = (co->diameter * co->diameter) / (co->height * co->height);
    return (vec_normalize(sub_vec(hc, mult_vec(axis, (1 + m) * proj))));
	}
	else if (part == 1)
		return (axis);
	return (mult_vec(axis, -1.0));
}

t_inter	hit_cone_update(t_inter best, t_objs *obj, t_ray *ray)
{
	static t_inter hit;
	t_cylinder *co;
	double t;
	int part;
	t_vec axis;

	co = (t_cylinder *)obj->data;
	if (!cone_intersection(ray, co, &t, &part))
		return (best);
	if (best.t > 0.0 && t >= best.t)
		return (best);
	axis = vec_normalize(co->normal);
	hit = best;
	hit.t = t;
	hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
	hit.color = co->color;
	hit.norm = co->normal;
	hit.norm = co_part_normal(co, axis, hit.hit, part);
	if (dot_vec(hit.norm, ray->dir) > 0.0)
		hit.norm = mult_vec(hit.norm, -1.0);
	return (hit);
}