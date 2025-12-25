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

t_vec add_vec(t_vec u, t_vec v)
{
    t_vec w;

    w.x = u.x + v.x;
    w.y = u.y + v.y;
    w.z = u.z + v.z;
    return (w);
}

t_vec mult_vec(t_vec v, double a)
{
    t_vec w;

    w.x = v.x * a;
    w.y = v.y * a;
    w.z = v.z * a;
    return (w);
}
