#include "../include/minirt.h"

static void	validate_cylinder_tokens(t_data *data, char **tokens)
{
	if (!tokens || split_len(tokens) != 6)
	{
		free_split(tokens);
		ft_err("Invalid number of cylinder parameter", &data->gc_root, 1);
	}
	if (has_invalid_input(tokens[1]) || has_invalid_input(tokens[2])
		|| has_invalid_input(tokens[3]) || has_invalid_input(tokens[4])
		|| has_invalid_input(tokens[5]))
	{
		free_split(tokens);
		ft_err("Invalid cylinder input parameter!", &data->gc_root, 1);
	}
}

static t_objs	*create_cylinder_obj(t_data *data, char **tokens)
{
	t_objs	*new;

	new = alloc_object(OBJ_CYLINDER, &data->gc_root);
	if (!new)
	{
		free_split(tokens);
		ft_err("Failed to allocate in cylinder!", &data->gc_root, 1);
	}
	new->next = NULL;
	return (new);
}

static void	set_cylinder_center_normal(t_data *data, t_cylinder *cy,
		char **tokens)
{
	if (get_vec(tokens[1], &cy->center))
	{
		free_split(tokens);
		ft_err("Invalid cylinder center!", &data->gc_root, 1);
	}
	if (get_vec(tokens[2], &cy->normal) || is_out_of_bounds(&cy->normal))
	{
		free_split(tokens);
		ft_err("Invalid cylinder axis vector [-1,1] and not zero!",
			&data->gc_root, 1);
	}
	cy->normal = vec_normalize(cy->normal);
}

static void	set_cylinder_attributes(t_data *data, t_cylinder *cy, char **tokens)
{
	cy->diameter = ft_atod(tokens[3]);
	if (cy->diameter <= 0)
	{
		free_split(tokens);
		ft_err("Cylinder diameter must be > 0!", &data->gc_root, 1);
	}
	cy->height = ft_atod(tokens[4]);
	if (cy->height < 0)
	{
		free_split(tokens);
		ft_err("Cylinder height must be > 0!", &data->gc_root, 1);
	}
	if (get_color(tokens[5], &cy->color))
	{
		free_split(tokens);
		ft_err("Invalid cylinder color!", &data->gc_root, 1);
	}
}

void	parse_cylinder(t_data *data, char **tokens)
{
	t_objs		*new;
	t_cylinder	*cy;

	validate_cylinder_tokens(data, tokens);
	new = create_cylinder_obj(data, tokens);
	cy = (t_cylinder *)new->data;
	set_cylinder_center_normal(data, cy, tokens);
  printf("[%f]\n", cy->height);
	set_cylinder_attributes(data, cy, tokens);
  if (cy->height == 0.0)
    new->type = OBJ_TUBE;
	add_object_to_scene(&data->scene, new);
}
