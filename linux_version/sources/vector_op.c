#include "../include/minirt.h"

t_vec vec_cross(t_vec u, t_vec v)
{
    t_vec w;
    w.x = (u.y * v.z) - (u.z * v.y);
    w.y = (u.z * v.x) - (u.x * v.z);
	w.z = (u.x * v.y) - (u.y * v.x);
    return (w);
}

t_vec vec_normalize(t_vec v)
{
    t_vec normalized;
    double len;

    len = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    if (len < EPSILON)
        return ((t_vec){0,0,0});
    normalized.x = v.x / len;
    normalized.y = v.y / len;
    normalized.z = v.z / len;

    return (normalized);
}

double dot_vec(t_vec a, t_vec b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

t_vec normalize_color(t_vec rgb)
{
    return ((t_vec) {
        rgb.x/255,
        rgb.y/255,
        rgb.z/255,
    });
}
