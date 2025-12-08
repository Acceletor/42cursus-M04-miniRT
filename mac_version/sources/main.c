#include "../include/minirt.h"

// void parse_identifier(char* id, char**tokens, t_scene *sc)
// {
//     if (ft_strcmp(id, "A") == 0)
//         parse_ambient();
//     else if (ft_strcmp(id, "C") == 0)
//         parse_camera();
//     else if (ft_strcmp(id, "L") == 0)
//         parse_light();
//     else if (ft_strcmp(id, "sp") == 0)
//         parse_sphere();
//     else if (ft_strcmp(id, "pl") == 0)
//         parse_plane();
//     else if (ft_strcmp(id, "cy") == 0)
//         parse_cylinder();
//     else
//         ft_err("Invaid Object Type", );
    
// }

// int parse(t_scene *sc, int fd, t_collector *g_root)
// {
//     char **tokens;

//     while(1)
//     {
//         tokens = ft_split(get_next_line(fd), ' ');
//         if (!tokens)
//             break;
//         if (*tokens)
//             parse_identifier(*tokens, tokens, sc);
        
//     }
//     close(fd);
// }


int main(int argc, char **argv)
{
    t_data data;

    data.gc_root = NULL;
    data.fd = -1;
    if (invalid_file(argc, argv, &data))
        ft_err("Incorrect argument: ./miniRT file_name.rt", &data.gc_root);
    if (!allocate_scene(&data))
        ft_err("allocation", &data.gc_root);
    // parse(&data);
    // .......program logic.......
    gc_free_all(&data.gc_root);
    // close(fd)
    return 0;
}