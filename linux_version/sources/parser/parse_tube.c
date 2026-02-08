#include "../include/minirt.h"

static void	validate_tube_tokens(t_data *data, char **tokens)
{
	if (!tokens || split_len(tokens) != 6)
	{
		free_split(tokens);
		ft_err("Invalid number of tube parameter", &data->gc_root, 1);
	}
	if (has_invalid_input(tokens[1]) || has_invalid_input(tokens[2])
		|| has_invalid_input(tokens[3]) || has_invalid_input(tokens[4])
		|| has_invalid_input(tokens[5]))
	{
		free_split(tokens);
		ft_err("Invalid tube input parameter!", &data->gc_root, 1);
	}
}

static t_objs	*create_tube_obj(t_data *data, char **tokens)
{
	t_objs	*new;

	new = alloc_object(OBJ_TUBE, &data->gc_root);
	if (!new)
	{
		free_split(tokens);
		ft_err("Failed to allocate in tube!", &data->gc_root, 1);
	}
	new->next = NULL;
	return (new);
}

static void	set_tube_center_normal(t_data *data, t_cylinder *cy,
		char **tokens)
{
	if (get_vec(tokens[1], &cy->center))
	{
		free_split(tokens);
		ft_err("Invalid tube center!", &data->gc_root, 1);
	}
	if (get_vec(tokens[2], &cy->normal) || is_out_of_bounds(&cy->normal))
	{
		free_split(tokens);
		ft_err("Invalid tube axis vector [-1,1] and not zero!",
			&data->gc_root, 1);
	}
	cy->normal = vec_normalize(cy->normal);
}

static void	set_tube_attributes(t_data *data, t_cylinder *cy, char **tokens)
{
	cy->diameter = ft_atod(tokens[3]);
	if (cy->diameter <= 0)
	{
		free_split(tokens);
		ft_err("Tube diameter must be > 0!", &data->gc_root, 1);
	}
	cy->height = ft_atod(tokens[4]);
	if (cy->height < 0)
	{
		free_split(tokens);
		ft_err("Tube height must be >= 0!", &data->gc_root, 1);
	}
	if (get_color(tokens[5], &cy->color))
	{
		free_split(tokens);
		ft_err("Invalid tube color!", &data->gc_root, 1);
	}
}

void	parse_tube(t_data *data, char **tokens)
{
	t_objs		*new;
	t_cylinder	*tu;

	validate_tube_tokens(data, tokens);
	new = create_tube_obj(data, tokens);
	tu = (t_cylinder *)new->data;
	set_tube_center_normal(data, tu, tokens);
	set_tube_attributes(data, tu, tokens);
	add_object_to_scene(&data->scene, new);
}
