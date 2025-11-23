#include "../include/minirt.h"

void ft_err(char *str)
{
    ft_printf("Error: %s\n", str);
    // free_everything()
    exit(1);
}


int check_file(int argc, char **argv, int *fd)
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
    *fd = open(argv[1], O_RDONLY);
    if (*fd == -1)
        ft_err("failed to read the file");
    return (0);
}

int main(int argc, char **argv)
{
    // t_scene *sc;
    int fd;

    if (check_file(argc, argv, &fd))
        ft_err("Incorrect argument: ./miniRT file_name.rt");
    // allocate_scene(sc);
    ft_printf("continue...\n");
    // close(fd)

    return 0;
}