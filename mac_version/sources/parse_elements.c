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
    if (has_invalid_input(tokens[1]) || has_invalid_input(tokens[2]))
    {
        free_split(tokens);
        ft_err("Ambient has invalid input!", &data->gc_root, 1);
    }
    data->scene.amb.ratio = ft_atod(tokens[1]);
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
    data->scene.amb.is_set = true;
}

void parse_camera(t_data *data, char **tokens)
{
    if (!tokens || split_len(tokens) != 4)
    {
        free_split(tokens);
        ft_err("invalid camera!", &data->gc_root, 1);
    }
    if (data->scene.cam.is_set == true)
    {
        free_split(tokens);
        ft_err("Too many camera!", &data->gc_root, 1);
    }
    if (has_invalid_input(tokens[1]) || has_invalid_input(tokens[2])
        || has_invalid_input(tokens[3]))
    {
        free_split(tokens);
        ft_err("Camera has invalid input!", &data->gc_root, 1);
    }
    if ( get_vec(tokens[1], &data->scene.cam.pos) 
        || get_vec(tokens[2], &data->scene.cam.dir))
    {
        free_split(tokens);
        ft_err("Invalid Camera Vector!", &data->gc_root, 1);
    }
    if (data->scene.cam.dir.x > 1 || data->scene.cam.dir.y > 1 || data->scene.cam.dir.z > 1
        || data->scene.cam.dir.x < -1 || data->scene.cam.dir.y < -1 
        || data->scene.cam.dir.z < -1)
    {
        free_split(tokens);
        ft_err("Invalid Camera orientation!", &data->gc_root, 1);
    }
    data->scene.cam.fov = ft_atod(tokens[3]);
    if (data->scene.cam.fov < 0 || data->scene.cam.fov > 180)
    {
        free_split(tokens);
        ft_err("Camera's FOV: Horizontal field of view in degrees in the range [0,180]", &data->gc_root, 1);
    }
    data->scene.cam.is_set = true;
}
