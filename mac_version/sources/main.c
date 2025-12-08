#include "../include/minirt.h"

void free_split(char **tokens)
{
    int i;

    i = 0;
    if (!tokens)
        return;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

void parse_identifier(char* id, char**tokens, t_data *data)
{
    if (ft_strcmp(id, "A") == 0)
        parse_ambient();
    else if (ft_strcmp(id, "C") == 0)
        parse_camera();
    else if (ft_strcmp(id, "L") == 0)
        parse_light();
    else if (ft_strcmp(id, "sp") == 0)
        parse_sphere();
    else if (ft_strcmp(id, "pl") == 0)
        parse_plane();
    else if (ft_strcmp(id, "cy") == 0)
        parse_cylinder();
    else
    {
        free_split(tokens);
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


int main(int argc, char **argv)
{
    t_data data;

    data.gc_root = NULL;
    data.fd = -1;
    if (invalid_file(argc, argv, &data))
        ft_err("Incorrect argument: ./miniRT file_name.rt", &data.gc_root);
    if (!allocate_scene(&data))
        ft_err("allocation", &data.gc_root);
    parse(&data);
    // .......program logic.......
    gc_free_all(&data.gc_root);
    // close(fd)
    return 0;
}