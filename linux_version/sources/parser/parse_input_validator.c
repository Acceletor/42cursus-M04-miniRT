#include "../include/minirt.h"

static int	check_double_body(char *s, int i)
{
	int	has_dot;
	int	has_before;
	int	has_after;

	has_dot = 0;
	has_before = 0;
	has_after = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) && !has_dot)
			has_before = 1;
		else if (s[i] == '.' && !has_dot)
			has_dot = 1;
		else if (ft_isdigit(s[i]) && has_dot)
			has_after = 1;
		else
			return (1);
		i++;
	}
	if (!has_before)
		return (1);
	if (has_dot && !has_after)
		return (1);
	return (0);
}

int	is_invalid_double(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (1);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (s[i] == '\0')
		return (1);
	return (check_double_body(s, i));
}

int	is_invalid_vector(char *s)
{
	char	**parts;
	int		i;

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

int	has_invalid_input(char *token)
{
	int	commas;
	int	i;

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


int is_out_of_bounds(t_vec *v) {
  if (v->x > 1
    || v->y > 1
		|| v->z > 1 
    || v->x < -1 
    || v->y < -1
		|| v->z < -1 
    || (v->x == 0 && v->y == 0&& v->z == 0)
  )
    return (1);
  else 
    return (0);
}
