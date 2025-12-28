#include "../include/minirt.h"

t_vec sub_vec(t_vec a, t_vec b)
{
    return (t_vec) {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

double dot_vec(t_vec a, t_vec b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

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

int sphere_intersect(t_ray *ray, t_sphere *sp ,double *t_hit)
{
    t_sp_tmp sph;
    double t;

    sph.r = sp->diameter * 0.5;
    sph.oc = sub_vec(ray->origin, sp->center);
    sph.a = dot_vec(ray->dir, ray->dir);
    sph.b = 2.0 * dot_vec(ray->dir, sph.oc);
    sph.c = dot_vec(sph.oc, sph.oc) - (sph.r * sph.r);
    sph.disc = (sph.b * sph.b) - (4.0 * sph.a * sph.c);
    if (sph.disc < 0.0)
        return (0);
    sph.sqrt_disc = sqrt(sph.disc);
    sph.t1 = (-sph.b - sph.sqrt_disc) / (2.0 * sph.a);
	sph.t2 = (-sph.b + sph.sqrt_disc) / (2.0 * sph.a);
    t = get_smallest_positive(sph.t1, sph.t2);
    if (t < 0.0)
		return (0);
	*t_hit = t;
	return (1);
}

t_inter hit_sphere_update(t_inter best, t_objs *obj, t_ray *ray)
{
    t_inter hit;
    t_sphere *sp;
    double t;

    sp = (t_sphere *)obj->data;
    if (!sphere_intersect(ray, sp, &t))
        return (best);
    
    if (best.t > 0.0 && t >= best.t)
        return (best);
    
    hit = best;
    hit.t = t;
    hit.hit = add_vec(ray->origin, mult_vec(ray->dir, t));
    hit.norm = vec_normalize(sub_vec(hit.hit, sp->center));
    hit.color = sp->color;

    return (hit);
}

t_inter scene_inter(t_ray *ray, t_scene *sc)
{
    t_inter best;
    t_objs *obj;

    best.t = -1.0;
    best.hit = (t_vec){0,0,0};
    best.norm = (t_vec){0,0,0};
    best.color = (t_vec){0,0,0};
    obj = sc->objs;
    while(obj)
    {
        if (obj->type == OBJ_SPHERE)
            best = hit_sphere_update(best, obj, ray);
        // else if (obj->type == OBJ_PLANE)
        //     hold = plane_normal();
        // else if (obj->type == OBJ_CYLINDER)
        //     hold = cylinder_normal();
        obj = obj->next;
    }
    return (best);
}


t_vec   ray_color(t_ray *ray, t_scene *sc)
{
    t_inter inter;
    // t_vec px_col;
    // t_vec amb;
    
    inter = scene_inter(ray, sc);
    if (inter.t > EPSILON)
    {
        // compute amb + light;
        // return (inter.color); //temp
        return (t_vec){1.0, 0.0, 0.0};
    }
    return (t_vec){0.2, 0.2, 0.2};
    // return (mult_vec(sc->amb.color, sc->amb.ratio)); //background
}

t_ray ray_primary(t_camera *cam, double sx, double sy)
{
    t_ray ray;
    double horizontal_offset;
    double vertical_offset;

    horizontal_offset = sx * (cam->vp_width * 0.5);
    vertical_offset = sy * (cam->vp_height * 0.5);

    ray.origin = cam->pos;
    ray.dir = add_vec(cam->forward,
                add_vec(
                    mult_vec(cam->right, horizontal_offset), 
                    mult_vec(cam->up, vertical_offset)
                ));
    ray.dir = vec_normalize(ray.dir);
    return (ray);
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel/8));
    *(unsigned int *)dst = (unsigned int)color;
}

static int to_byte(double x)
{
    if (x <= 0.0) return 0;
    if (x >= 1.0) return 255;
    return (int)(x * 255.999);
}

int create_rgb(int r, int g, int b) 
{
    return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff)); 
}

int vec_to_rgb(t_vec c) // expects 0..1
{
    return create_rgb(to_byte(c.x), to_byte(c.y), to_byte(c.z));
}

void draw(t_renderer *info, t_scene *sc)
{  
    info->y = 0;
    while (info->y < HEIGHT)
    {
        info->x = 0;
        while (info->x < WIDTH)
        {
            info->sx = ((info->x + 0.5)/ (double)WIDTH) * 2.0 - 1.0;
            info->sy = 1.0 - ((info->y + 0.5)/ (double)HEIGHT) * 2.0;
            info->ray = ray_primary(&info->cam, info->sx, info->sy);
            info->ray_col = ray_color(&info->ray, sc);
            my_mlx_pixel_put(&info->img, info->x, info->y,
                vec_to_rgb(info->ray_col));
            info->x++;
        }
        info->y++;
    }
    mlx_put_image_to_window(info->mlx.mlx, info->mlx.win, info->img.img, 0, 0);
}

void rendering(t_scene *sc)
{
    t_renderer info;

    info.cam = set_camera(sc);
    image_init(&info);
    draw(&info, sc);
    mlx_loop(info.mlx.mlx);
}