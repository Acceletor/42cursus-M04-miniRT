#include "../include/minirt.h"
t_vec	make_vec(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

int get_vec(char *str, t_vec *out)
{
    char **params;

    params = ft_split(str, ',');
    if (!params)
        return (1);
    if (split_len(params) != 3)
    {
        free_split(params);
        return (1);
    }
    *out = make_vec(ft_atod(params[0]), ft_atod(params[1]), ft_atod(params[2]));
    free_split(params);
    return (0);
}
int split_len(char **tokens)
{
    int i = 0;
    while (tokens && tokens[i])
        i++;
    return i;
}

int get_color(char *str, t_vec *out)
{
    char **params;
    t_vec color;

    params = ft_split(str, ',');
    if (!params)
        return (1); //malloc error
    if (split_len(params) != 3)
    {
        free_split(params);
        return (2); //format error
    }
    color = make_vec(ft_atod(params[0]), ft_atod(params[1]), ft_atod(params[2]));
    if (color.x != (int)color.x || color.y != (int)color.y || color.z != (int)color.z ||
        color.x > 255 || color.y > 255 || color.z > 255 ||
        color.x < 0 || color.y < 0 || color.z < 0)
    {
        free_split(params);
        return (3); //invalid color
    }
    out->x = (int)color.x;
    out->y = (int)color.y;
    out->z = (int)color.z;
    free_split(params);
    return (0);
}
