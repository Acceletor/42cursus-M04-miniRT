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

int is_within(t_ray *ray, t_cylinder *cy, t_vec axis, double t)
{
  t_vec		p;
	double		y;

  p = add_vec(ray->origin, mult_vec(ray->dir, t));
  y = dot_vec(sub_vec(p, cy->center), axis);
  if (fabs(y) > cy->height * 0.5)
    return (0);
  return (1);
}

double	get_smallest_positive_within(t_ray *ray, t_cylinder *cy, t_vec axis, t_cy_quad	q)
{
  if (q.t1 > EPSILON && is_within(ray, cy, axis, q.t1))
  {
    if (q.t2 > EPSILON && is_within(ray, cy, axis, q.t2))
    {
      if (q.t1 < q.t2)
  			return (q.t1);
    }
    return (q.t1);
  } 
  else if (q.t2 > EPSILON && is_within(ray, cy, axis, q.t2))
  {
    return (q.t2);
  }
	return (-1.0);
}