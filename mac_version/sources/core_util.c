#include "../include/minirt.h"

int invalid_file(int argc, char **argv, t_data *data)
{
    int len;
    if (argc != 2)
        return (1);
    len = ft_strlen(argv[1]);
    if (len < 3)
        return (1);
    if (argv[1][len - 3] != '.' ||
        argv[1][len - 2] != 'r' ||
        argv[1][len - 1] != 't')
        return (1);
    data->fd = open(argv[1], O_RDONLY);
    if (data->fd == -1)
        ft_err("failed to read the file", &data->gc_root);
    return (0);
}