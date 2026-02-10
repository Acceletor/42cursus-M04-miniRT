#include "../include/minirt.h"

static void	validate_circle_tokens(t_data *data, char **tokens)
{
	if (!tokens || split_len(tokens) != 5)
	{
		free_split(tokens);
		ft_err("Invalid number of circle parameter!", &data->gc_root, 1);
	}
	if (has_invalid_input(tokens[1]) || has_invalid_input(tokens[2])
		|| has_invalid_input(tokens[3]) || has_invalid_input(tokens[3]))
	{
		free_split(tokens);
		ft_err("Invalid circle input parameter!", &data->gc_root, 1);
	}
}

static t_objs	*create_circle_obj(t_data *data, char **tokens)
{
	t_objs	*new;

	new = alloc_object(OBJ_CIRCLE, &data->gc_root);
	if (!new)
	{
		free_split(tokens);
		ft_err("Failed to allocate in circle!", &data->gc_root, 1);
	}
	new->next = NULL;
	return (new);
}

static void	set_circle_center_normal(t_data *data, t_circle *ci, char **tokens)
{
	if (get_vec(tokens[1], &ci->center))
	{
		free_split(tokens);
		ft_err("Invalid circle center!", &data->gc_root, 1);
	}
	if (get_vec(tokens[2], &ci->normal) || is_out_of_bounds(&ci->normal))
	{
		free_split(tokens);
		ft_err("Invalid circle axis vector [-1,1] and not zero!",
			&data->gc_root, 1);
	}
	ci->normal = vec_normalize(ci->normal);
}

static void	set_circle_attributes(t_data *data, t_circle *ci, char **tokens)
{
	ci->diameter = ft_atod(tokens[3]);
	if (ci->diameter <= 0)
	{
		free_split(tokens);
		ft_err("Circle diameter must be > 0!", &data->gc_root, 1);
	}
	if (get_color(tokens[4], &ci->color))
	{
		free_split(tokens);
		ft_err("Invalid circle color!", &data->gc_root, 1);
	}
}

void	parse_circle(t_data *data, char **tokens)
{
	t_objs		*new;
	t_circle	*ci;

	validate_circle_tokens(data, tokens);
	new = create_circle_obj(data, tokens);
	ci = (t_circle *)new->data;
	set_circle_center_normal(data, ci, tokens);
	set_circle_attributes(data, ci, tokens);
	add_object_to_scene(&data->scene, new);
}
