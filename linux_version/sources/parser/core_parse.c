#include "../include/minirt.h"

void	parse_identifier(char *id, char **tokens, t_data *data)
{
	if (ft_strcmp(id, "A") == 0)
		parse_ambient(data, tokens);
	else if (ft_strcmp(id, "C") == 0)
		parse_camera(data, tokens);
	else if (ft_strcmp(id, "L") == 0)
		parse_light(data, tokens);
	else if (ft_strcmp(id, "sp") == 0)
		parse_sphere(data, tokens);
	else if (ft_strcmp(id, "pl") == 0)
		parse_plane(data, tokens);
	else if (ft_strcmp(id, "cy") == 0)
		parse_cylinder(data, tokens);
	else if (ft_strcmp(id, "tu") == 0)
		parse_tube(data, tokens);
	else if (ft_strcmp(id, "co") == 0)
		parse_cone(data, tokens);
	else if (ft_strcmp(id, "ci") == 0)
		parse_circle(data, tokens);
	else if (ft_strcmp(id, "#") == 0)
		return ;
	else
	{
		free_split(tokens);
		ft_err("Invaid Object Type", &data->gc_root, 1);
	}
}

void	trim_line_newline(char *s)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}

int	parse(t_data *data)
{
	char	*line;
	char	**tokens;

	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
			break ;
		trim_line_newline(line);
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
