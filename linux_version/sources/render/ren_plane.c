#include "../include/minirt.h"

/*
Normal - object perpendicular to a given object.
Any vector on the plain is perpendicular to v_normal
Equation of the plane (P − P_0) . v_normal = 0
Point on a ray P = Origin + t . d

t = dot(sub(P0, O), n) / dot(d, n)

dot of dir and normal (checking the angle)
  if dot == 0 then angle == 90

p0_to_o - (vector from plane_origin to origin)

dot of p0_to_o and normal

dot(p0_to_o, normal) / dot(dir, normal)

t - distance to hit.
t = ((P_0 - Origin) . v_n) / (v_dir . v_n)
if t < 0 then behind the camera.

dist = p0_to_o * cos(p0_to_o, n)

          .
          |\< 01 cos = (dist / t)
          | \
          |  \
   (dist) |   \ (t?)
          |    \
          |     \  
        __|______\__ Plane
          P0     |P
                 | (n_v)
                 V 

t = dist / cos(01)
t = Sortest Distance to Plane Origin / Rate of perpendicular travel
*/
static int	plane_intersection(t_ray *ray, t_plane *pl, double *t_hit)
{
	double	den;
	t_vec	p0_to_o;
	double	t;

	den = dot_vec(ray->dir, pl->normal);
	if (fabs(den) < EPSILON)
		return (0);
	p0_to_o = sub_vec(pl->point, ray->origin);
	t = dot_vec(p0_to_o, pl->normal) / den;
	if (t <= EPSILON)
		return (0);
	*t_hit = t;
	return (1);
}

/*
  is closest hit check
  hit.hit - coordinates of the hit - P = v_origin + t*v_dir
  if plane hit from behind flip hit.norm
*/
t_inter	hit_plane_update(t_inter best, t_objs *obj, t_ray *ray)
{
	t_inter	hit;
	t_plane	*pl;
	double	t;

	pl = (t_plane *)obj->data;
	if (!plane_intersection(ray, pl, &t))
		return (best);
	if (best.t > EPSILON && t >= best.t)
		return (best);
	hit = best;
	hit.t = t;
	hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
	hit.norm = vec_normalize(pl->normal);
	if (dot_vec(hit.norm, ray->dir) > 0.0)
		hit.norm = vec_normalize(mult_vec(hit.norm, -1.0));
	hit.color = pl->color;
	return (hit);
}