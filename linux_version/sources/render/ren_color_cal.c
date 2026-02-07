#include "../include/minirt.h"

static t_vec	ambient_color(t_scene *sc, t_vec obj_color)
{
	t_vec	a;

	// a = mult_vec(normalize_color(sc->amb.color), sc->amb.ratio);
	a = mult_vec(sc->amb.color, sc->amb.ratio);
	return (hadamard(obj_color, a));
}

static t_vec	diffuse_color(t_vec obj, t_light *li, t_vec n, t_vec ldir)
{
	double	ndotl;
	t_vec	li_col;

	ndotl = dot_vec(n, ldir);
	if (ndotl < 0.0)
		ndotl = 0.0;
	// li_col = mult_vec(normalize_color(li->color), li->ratio);
	li_col = mult_vec(li->color, li->ratio);
	li_col = mult_vec(li_col, ndotl);
	return (hadamard(obj, li_col));
}

static int	in_shadow(t_scene *sc, t_inter inter, t_light *li)
{
	t_ray	shadow;
	t_inter	block;
	t_vec	to_light;
	double	dist_to_li;

	shadow.origin = add_vec(inter.hit, mult_vec(inter.norm, EPSILON));
	to_light = sub_vec(li->pos, shadow.origin);
	dist_to_li = sqrt(dot_vec(to_light, to_light));
	shadow.dir = vec_normalize(to_light);
	block = scene_inter(&shadow, sc);
	if (block.t > EPSILON && block.t < dist_to_li)
		return (1);
	return (0);
}

static t_vec	specular_color(t_scene *sc, t_inter inter, t_light *li, t_vec ldir)
{
	t_vec	vdir;
	t_vec	h;
	double	ndoth;
	double	spec;
	double	shininess;

	// View direction: from hit point to camera
	vdir = vec_normalize(sub_vec(sc->cam.pos, inter.hit));
	// Half vector H = normalize(L + V)
	h = vec_normalize(add_vec(ldir, vdir));
	ndoth = fmax(dot_vec(inter.norm, h), 0.0);
	shininess = 256; // try 32, 64, 128
	spec = pow(ndoth, shininess);
	return (mult_vec(li->color, li->ratio * spec));
}

t_vec	shade_hit(t_scene *sc, t_inter inter)
{
	t_vec	col;
	t_light	*li;
	t_vec	ldir;

	col = ambient_color(sc, inter.color);
	li = sc->light;
	while (li)
	{
		if (!in_shadow(sc, inter, li))
		{
			ldir = vec_normalize(sub_vec(li->pos, inter.hit));
			col = add_vec(col, diffuse_color(inter.color, li, inter.norm,
						ldir));
			col = add_vec(col, specular_color(sc, inter, li, ldir));
		}
		li = li->next;
	}
	return (clamp01(col));
}
