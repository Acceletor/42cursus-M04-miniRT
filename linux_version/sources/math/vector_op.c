#include "../include/minirt.h"

/*
vector cross product (u x v) by Laplace Expansion
[w_x w_y w_z]
[u_x u_y u_z]
[v_x v_y v_z]

for given matrix coordinates (i, j)
Cofactor_ij ​= (−1)^(i+j) * Minor_ij​

Looking for [w_x w_y w_z].

Symmetry cancels out to zero.
*/
t_vec	vec_cross(t_vec u, t_vec v)
{
	t_vec	w;

	w.x = (u.y * v.z) - (u.z * v.y);
	w.y = (u.z * v.x) - (u.x * v.z);
	w.z = (u.x * v.y) - (u.y * v.x);
	return (w);
}

/*
Converts a vector to a 'unit verctor' (len of 1) while preserving direction. Pure direction vectors.
EPSILON - a tiny number for division by zero checks
*/
t_vec	vec_normalize(t_vec v)
{
	t_vec	normalized;
	double	len;

	len = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	if (len < EPSILON)
		return ((t_vec){0, 0, 0});
	normalized.x = v.x / len;
	normalized.y = v.y / len;
	normalized.z = v.z / len;
	return (normalized);
}

/*
Used for finding the angle between vectors. (alignment)
product > 0 - less than 90 (in the same direction)
product == 0 - 90
product < - more than 90 (opposite directions)

A * B * cos (cosinus value determines sign)
*/
double	dot_vec(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	normalize_color(t_vec rgb)
{
	return ((t_vec){
		rgb.x / 255,
		rgb.y / 255,
		rgb.z / 255,
	});
}
