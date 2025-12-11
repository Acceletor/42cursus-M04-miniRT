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
