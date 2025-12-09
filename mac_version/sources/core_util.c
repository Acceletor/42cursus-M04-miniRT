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
        ft_err("failed to read the file", &data->gc_root, 1);
    return (0);
}

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

double	ft_atod(const char *s)
{
	double	res;
	double	div;
	int		sign;

	res = 0.0;
	div = 1.0;
	sign = 1;
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		res = res * 10 + (*s++ - '0');
	if (*s == '.')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s++ - '0');
		div *= 10.0;
	}
	return ((res / div) * sign);
}