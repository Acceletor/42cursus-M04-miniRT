#include "../include/minirt.h"

static int	co_pick_best(t_co_hits h, double *t_best, int *part)
{
	*t_best = -1.0;
	*part = -1;
	if (h.t_side > EPSILON && (*t_best < 0.0 || h.t_side < *t_best))
		(*t_best = h.t_side, *part = 0);
	if (h.t_bot > EPSILON && (*t_best < 0.0 || h.t_bot < *t_best))
		(*t_best = h.t_bot, *part = 1);
	return (*t_best > 0.0);
}


static void co_bot_init(t_circle *bot, t_cylinder *co, t_vec axis)
{
  bot->diameter = co->diameter;
  bot->center = sub_vec(co->center, mult_vec(axis, co->height * 0.5));
  bot->normal = mult_vec(axis, -1.0);
  bot->color = co->color;
}

static int	cone_intersection(t_ray *ray, t_cylinder *co, double *t_hit,
		int *part)
{
  t_circle	bot;
  t_vec axis;
	t_co_hits	h;
	double		t_best;

	h.t_side = -1.0;
	h.t_bot = -1.0;
  axis = vec_normalize(co->normal);
	co_bot_init(&bot, co, axis);
	co_side_hit(ray, co, axis, &h.t_side);
  circle_intersection(ray, &bot, &h.t_bot);
	if (!co_pick_best(h, &t_best, part))
		return (0);
	*t_hit = t_best;
	return (1);
}

static t_vec	co_part_normal(t_cylinder *co, t_vec axis, t_vec hit, int part)
{
	t_vec	v;
	double	proj;

	if (part == 0)
	{
		v = sub_vec(hit, co->center);
		proj = dot_vec(v, axis);
		return (vec_normalize(sub_vec(v, mult_vec(axis, proj))));
	}
  return (mult_vec(axis, -1.0));
}


t_inter	hit_cone_update(t_inter best, t_objs *obj, t_ray *ray)
{
  static t_inter hit;
  t_cylinder *co;
  double		t;
	int			part;
	t_vec		axis;

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