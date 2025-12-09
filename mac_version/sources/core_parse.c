#include "../include/minirt.h"

void parse_ambient(t_data *data, char **tokens)
{
    // t_amb amb; 
    if ( !tokens || ft_strlen(*tokens) != 3)
        ft_err("invalid ambient!", &data->gc_root);
    if (data->scene.amb.is_set == true)
        ft_err("Too many ambient!", &data->gc_root);
    // amb.ratio = tokens[1]
    
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
        close(data->fd);
        ft_err("Invaid Object Type", &data->gc_root);
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
            ft_err("malloc failed in ft_split", &data->gc_root);
        if (*tokens)
            parse_identifier(*tokens, tokens, data);
        free_split(tokens);
    }
    close(data->fd);
    return (0);
}