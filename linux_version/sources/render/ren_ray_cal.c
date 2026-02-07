#include "../include/minirt.h"

t_inter	scene_inter(t_ray *ray, t_scene *sc)
{
	t_inter	best;
	t_objs	*obj;

	best.t = -1.0;
	best.hit = (t_vec){0, 0, 0};
	best.norm = (t_vec){0, 0, 0};
	best.color = (t_vec){0, 0, 0};
	obj = sc->objs;
	while (obj)
	{
		if (obj->type == OBJ_SPHERE)
			best = hit_sphere_update(best, obj, ray);
		else if (obj->type == OBJ_PLANE)
			best = hit_plane_update(best, obj, ray);
		else if (obj->type == OBJ_CYLINDER)
			best = hit_cylinder_update(best, obj, ray);
    else if (obj->type == OBJ_CONE)
			best = hit_cone_update(best, obj, ray);
		obj = obj->next;
	}
	return (best);
}

/*
  if ray hits an objec render shade.
  else render ambient.
*/
t_vec	ray_color(t_ray *ray, t_scene *sc)
{
	t_inter	inter;

	inter = scene_inter(ray, sc);
	if (inter.t > EPSILON)
	{
		// return (inter.color);
		return (shade_hit(sc, inter));
	}
  else
  {
    // return (mult_vec(normalize_color(sc->amb.color), sc->amb.ratio));
    return (mult_vec(sc->amb.color, sc->amb.ratio));
  }
}

/*
  Scales s_coordinates to viewport scale.
  Scales right and up vectors by respective offset, addes them. (2D plan direction)
  Then adds to the forward vector (3Difying)
*/
t_ray	ray_primary(t_camera *cam, double sx, double sy)
{
	t_ray ray;
	double horizontal_offset;
	double vertical_offset;

	horizontal_offset = sx * (cam->vp_width * 0.5);
	vertical_offset = sy * (cam->vp_height * 0.5);

	ray.origin = cam->pos;
	ray.dir = add_vec(cam->forward, add_vec(
    mult_vec(cam->right, horizontal_offset),
    mult_vec(cam->up, vertical_offset)
    ));
	ray.dir = vec_normalize(ray.dir);
	return (ray);
}