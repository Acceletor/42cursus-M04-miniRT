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