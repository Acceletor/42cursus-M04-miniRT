#include "../include/minirt.h"

t_vec sub_vec(t_vec a, t_vec b)
{
    return (t_vec) {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
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

t_vec hadamard(t_vec a, t_vec b)
{
    return ((t_vec){a.x*b.x, a.y*b.y, a.z*b.z});
}