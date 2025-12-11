#include "../include/minirt.h"
int is_invalid_double(char *s)
{
    int i;
    int has_dot;
    int has_digit;

    i = 0;
    has_dot = 0;
    has_digit = 0;
    if (s[i] == '+' || s[i] == '-')
        i++;
    if (s[i] == '\0')
        return (1);
    while (s[i])
    {
        if (ft_isdigit(s[i]))
            has_digit = 1;
        else if (s[i] == '.' && !has_dot)
            has_dot = 1;
        else
            return(1);
        i++;
    }
    if (!has_digit)
        return (1);
    return(0);
}

int is_invalid_vector(char *s)
{
    char **parts;
    int i;

    parts = ft_split(s, ',');
    if (!parts)
        return (1);
    if (split_len(parts) != 3)
    {
        free_split(parts);
        return (1);
    }
    i = 0;
    while (i < 3)
    {
        if (parts[i][0] == '\0' || is_invalid_double(parts[i]))
        {
            free_split(parts);
            return (1);
        }
        i++;
    }
    free_split(parts);
    return (0);
}

int has_invalid_input(char *token)
{
    int commas;
    int i;

    commas = 0;
    i = 0;
    while (token[i])
    {
        if (token[i] == ',')
            commas++;
        i++;
    }
    if (commas == 0)
        return (is_invalid_double(token));
    if (commas == 2)
        return (is_invalid_vector(token));
    return (1);
}


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

// int get_vec(char *str, t_vec *out)
// {
//     char **params;

//     params = ft_split(str, ',')

// }


// void parse_camera(t_data *data, char **tokens)
// {
//     if (!tokens || split_len(tokens) != 4)
//     {
//         free_split(tokens);
//         ft_err("invalid camera!", &data->gc_root, 1);
//     }
//     if (data->scene.cam.is_set == true)
//     {
//         free_split(tokens);
//         ft_err("Too many ambient!", &data->gc_root, 1);
//     }
//     if ( !get_vec(tokens[1], &data->scene.cam.pos) 
//         || !get_vec(tokens[2], &data->scene.cam.dir))
//     {
//         free_split(tokens);
//         ft_err("Invalid Camera Vector!", &data->gc_root, 1);
//     }
//     data->scene.cam.fov = ft_atod(tokens[3]);
//     data->scene.cam.is_set = true;
//     free_split
// }
