#include "../include/minirt.h"

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

    params = ft_split(str, ',');
    if (!params)
        return (1); //malloc error
    if (split_len(params) != 3)
    {
        free_split(params);
        return (2); //format error
    }
    *out = (t_vec){ft_atod(params[0]), ft_atod(params[1]), ft_atod(params[2])};
    // out->x = ft_atoi(params[0]);
    // out->y = ft_atoi(params[1]);
    // out->z = ft_atoi(params[2]);
    if (out->x > 255 || out->y > 255 || out->z > 255 
        || out->x < 0 || out->y < 0 || out->z < 0)
    {
        free_split(params);
        return (3); //invalid color
    }
    free_split(params);
    return (0);
}

void parse_identifier(char *id, char **tokens, t_data *data)
{
    if (ft_strcmp(id, "A") == 0)
        parse_ambient(data, tokens);
    // else if (ft_strcmp(id, "C") == 0)
    //     parse_camera();
    // else if (ft_strcmp(id, "L") == 0)
    //     parse_light();
    // else if (ft_strcmp(id, "sp") == 0)
    //     parse_sphere();
    // else if (ft_strcmp(id, "pl") == 0)
    //     parse_plane();
    // else if (ft_strcmp(id, "cy") == 0)
    //     parse_cylinder();
    else
    {
        free_split(tokens);
        ft_err("Invaid Object Type", &data->gc_root, 1);
    }
    
}

int parse(t_data *data)
{
    char *line;
    char **tokens;

    while(1)
    {
        line = get_next_line(data->fd);
        if (!line)
            break;
        tokens = ft_split(line, ' ');
        free(line);
        if (!tokens)
            ft_err("malloc failed in ft_split", &data->gc_root, 1);
        if (tokens[0] && tokens[0][0] != '\0' && tokens[0][0] != '\n')
            parse_identifier(*tokens, tokens, data);
        free_split(tokens);
    }
    close(data->fd);
    return (0);
}
