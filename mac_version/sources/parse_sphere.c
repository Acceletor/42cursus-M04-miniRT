#include "../include/minirt.h"

void	validate_sphere_tokens(t_data *data, char **tokens)
{
	if (!tokens || split_len(tokens) != 4)
	{
		free_split(tokens);
		ft_err("Invalid number of sphere's parameter!", &data->gc_root, 1);
	}
	if (has_invalid_input(tokens[1]) || has_invalid_input(tokens[2])
		|| has_invalid_input(tokens[3]))
	{
		free_split(tokens);
		ft_err("Invalid sphere input parameter!", &data->gc_root, 1);
	}
}

t_objs	*create_sphere_obj(t_data *data, char **tokens)
{
	t_objs	*new;

	new = alloc_object(OBJ_SPHERE, &data->gc_root);
	if (!new)
	{
		free_split(tokens);
		ft_err("Failed to allocate in Sphere!", &data->gc_root, 1);
	}
	new->next = NULL;
	return (new);
}

void	set_sphere_params(t_data *data, t_sphere *sp, char **tokens)
{
	if (get_vec(tokens[1], &sp->center))
	{
		free_split(tokens);
		ft_err("Invalid sphere center!", &data->gc_root, 1);
	}
	sp->diameter = ft_atod(tokens[2]);
	if (sp->diameter <= 0)
	{
		free_split(tokens);
		ft_err("Sphere diameter must be > 0!", &data->gc_root, 1);
	}
	if (get_color(tokens[3], &sp->color))
	{
		free_split(tokens);
		ft_err("Invalid sphere color!", &data->gc_root, 1);
	}
}

void	add_object_to_scene(t_scene *scene, t_objs *new)
{
	t_objs	*tmp;

	if (!scene->objs)
	{
		scene->objs = new;
		return ;
	}
	tmp = scene->objs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	parse_sphere(t_data *data, char **tokens)
{
	t_objs		*new;
	t_sphere	*sp;

	validate_sphere_tokens(data, tokens);
	new = create_sphere_obj(data, tokens);
	sp = (t_sphere *)new->data;
	set_sphere_params(data, sp, tokens);
	add_object_to_scene(&data->scene, new);
}
