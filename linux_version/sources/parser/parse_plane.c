#include "../include/minirt.h"

static void	validate_plane_tokens(t_data *data, char **tokens)
{
	if (!tokens || split_len(tokens) != 4)
	{
		free_split(tokens);
		ft_err("Invalid number of plane parameter!!", &data->gc_root, 1);
	}
	if (has_invalid_input(tokens[1]) || has_invalid_input(tokens[2])
		|| has_invalid_input(tokens[3]))
	{
		free_split(tokens);
		ft_err("Invalid plane input parameter!", &data->gc_root, 1);
	}
}

static t_objs	*create_plane_obj(t_data *data, char **tokens)
{
	t_objs	*new;

	new = alloc_object(OBJ_PLANE, &data->gc_root);
	if (!new)
	{
		free_split(tokens);
		ft_err("Failed to allocate in Plane!", &data->gc_root, 1);
	}
	new->next = NULL;
	return (new);
}

static void	set_plane_params(t_data *data, t_plane *pl, char **tokens)
{
	if (get_vec(tokens[1], &pl->point) || get_vec(tokens[2], &pl->normal))
	{
		free_split(tokens);
		ft_err("Invalid plane vector!", &data->gc_root, 1);
	}
	if (pl->normal.x < -1 || pl->normal.y < -1 || pl->normal.z < -1
		|| pl->normal.x > 1 || pl->normal.y > 1 || pl->normal.z > 1
		|| (pl->normal.x == 0 && pl->normal.y == 0 && pl->normal.z == 0))
	{
		free_split(tokens);
		ft_err("Invalid plane normal vector [-1,1] and not zero!",
			&data->gc_root, 1);
	}
	pl->normal = vec_normalize(pl->normal);
	if (get_color(tokens[3], &pl->color))
	{
		free_split(tokens);
		ft_err("Plane R,G,B colors have to be in [0-255]", &data->gc_root, 1);
	}
}

void	parse_plane(t_data *data, char **tokens)
{
	t_objs	*new;
	t_plane	*pl;

	validate_plane_tokens(data, tokens);
	new = create_plane_obj(data, tokens);
	pl = (t_plane *)new->data;
	set_plane_params(data, pl, tokens);
	add_object_to_scene(&data->scene, new);
}
