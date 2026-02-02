#include "../include/minirt.h"

void	validate_light_tokens(t_data *data, char **token)
{
	if (!token || split_len(token) != 4)
	{
		free_split(token);
		ft_err("Invalid Light!", &data->gc_root, 1);
	}
	if (has_invalid_input(token[1]) || has_invalid_input(token[2])
		|| has_invalid_input(token[3]))
	{
		free_split(token);
		ft_err("Invalid Light input parameter!", &data->gc_root, 1);
	}
}

t_light	*alloc_light(t_data *data, char **token)
{
	t_light	*new;

	new = gc_malloc(&data->gc_root, sizeof(t_light));
	if (!new)
	{
		free_split(token);
		ft_err("Failed to allocate Light!", &data->gc_root, 1);
	}
	new->next = NULL;
	return (new);
}

void	set_light_params(t_data *data, t_light *new, char **token)
{
    if (get_vec(token[1], &new->pos))
	{
		free_split(token);
		ft_err("Invalid light position!", &data->gc_root, 1);
	}
	new->ratio = ft_atod(token[2]);
	if (new->ratio > 1 || new->ratio < 0)
	{
		free_split(token);
		ft_err("The light brightness ratio must be in [0.0,1.0]!",
			&data->gc_root, 1);
	}
	if (get_color(token[3], &new->color))
	{
		free_split(token);
		ft_err("Invalid light color!!", &data->gc_root, 1);
	}
}

void	add_light_to_scene(t_scene *scene, t_light *new)
{
	t_light	*temp;

	if (!scene->light)
	{
		scene->light = new;
		return ;
	}
	temp = scene->light;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	parse_light(t_data *data, char **token)
{
	t_light	*new;

	validate_light_tokens(data, token);
	new = alloc_light(data, token);
	set_light_params(data, new, token);
	add_light_to_scene(&data->scene, new);
}
