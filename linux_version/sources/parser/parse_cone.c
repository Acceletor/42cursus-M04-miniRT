#include "../include/minirt.h"

static void	validate_cone_tokens(t_data *data, char **tokens)
{
	if (!tokens || split_len(tokens) != 6)
	{
		free_split(tokens);
		ft_err("Invalid number of cone parameter", &data->gc_root, 1);
	}
	if (has_invalid_input(tokens[1]) || has_invalid_input(tokens[2])
		|| has_invalid_input(tokens[3]) || has_invalid_input(tokens[4])
		|| has_invalid_input(tokens[5]))
	{
		free_split(tokens);
		ft_err("Invalid cone input parameter!", &data->gc_root, 1);
	}
}

static t_objs	*create_cone_obj(t_data *data, char **tokens)
{
	t_objs	*new;

	new = alloc_object(OBJ_CONE, &data->gc_root);
	if (!new)
	{
		free_split(tokens);
		ft_err("Failed to allocate in cone!", &data->gc_root, 1);
	}
	new->next = NULL;
	return (new);
}

static void	set_cone_center_normal(t_data *data, t_cone *co,
		char **tokens)
{
	if (get_vec(tokens[1], &co->center))
	{
		free_split(tokens);
		ft_err("Invalid cone center!", &data->gc_root, 1);
	}
	if (get_vec(tokens[2], &co->normal) || is_out_of_bounds(&co->normal))
	{
		free_split(tokens);
		ft_err("Invalid cone axis vector [-1,1] and not zero!",
			&data->gc_root, 1);
	}
	co->normal = vec_normalize(co->normal);
}

static void	set_cone_attributes(t_data *data, t_cone *co, char **tokens)
{
	co->diameter = ft_atod(tokens[3]);
	if (co->diameter <= 0)
	{
		free_split(tokens);
		ft_err("Cone diameter must be > 0!", &data->gc_root, 1);
	}
	co->height = ft_atod(tokens[4]);
	if (co->height <= 0)
	{
		free_split(tokens);
		ft_err("Cone height must be > 0!", &data->gc_root, 1);
	}
	if (get_color(tokens[5], &co->color))
	{
		free_split(tokens);
		ft_err("Invalid cone color!", &data->gc_root, 1);
	}
}


void	parse_cone(t_data *data, char **tokens)
{
  (void) data; (void) tokens;
	t_objs		*new;
	t_cone	*co;

	validate_cone_tokens(data, tokens);
	new = create_cone_obj(data, tokens);
	co = (t_cone *)new->data;
	set_cone_center_normal(data, co, tokens);
	set_cone_attributes(data, co, tokens);
	add_object_to_scene(&data->scene, new);
}
