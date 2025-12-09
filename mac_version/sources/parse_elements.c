#include "../include/minirt.h"


void parse_ambient(t_data *data, char **tokens)
{
    int check_color;

    if ( !tokens || split_len(tokens) != 3)
    {
        free_split(tokens);
        ft_err("invalid ambient!", &data->gc_root, 1);
    }
    if (data->scene.amb.is_set == true)
    {
        free_split(tokens);
        ft_err("Too many ambient!", &data->gc_root, 1);
    }
    data->scene.amb.ratio = ft_atod(tokens[1]);
    data->scene.amb.is_set = true;
    if (data->scene.amb.ratio < 0 || data->scene.amb.ratio > 1)
    {
        free_split(tokens);
        ft_err("Ambient lighting ratio in the range [0.0,1.0]", &data->gc_root, 1);
    }
    check_color = get_color(tokens[2], &data->scene.amb.color);
    if(check_color)
    {
        free_split(tokens);
        ft_err("Get ambient color!!", &data->gc_root, check_color);
    }
}