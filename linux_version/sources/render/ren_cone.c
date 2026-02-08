#include "../include/minirt.h"

t_inter	hit_cone_update(t_inter best, t_objs *obj, t_ray *ray)
{
  static t_inter hit;
  t_cylinder *co;

  co = (t_cylinder *)obj->data;
  (void) co;
  (void) best;
  (void) ray;
  return (hit);
}
