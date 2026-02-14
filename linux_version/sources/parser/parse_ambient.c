/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:02:32 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:02:33 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	validate_ambient_tokens(t_data *data, char **tokens)
{
	if (!tokens || split_len(tokens) != 3)
	{
		free_split(tokens);
		ft_err("invalid ambient!", &data->gc_root, 1);
	}
	if (data->scene.amb.is_set == true)
	{
		free_split(tokens);
		ft_err("Too many ambient!", &data->gc_root, 1);
	}
}

void	validate_ambient_values(t_data *data, char **tokens)
{
	if (has_invalid_input(tokens[1]) || has_invalid_input(tokens[2]))
	{
		free_split(tokens);
		ft_err("Ambient has invalid input!", &data->gc_root, 1);
	}
	data->scene.amb.ratio = ft_atod(tokens[1]);
	if (data->scene.amb.ratio < 0 || data->scene.amb.ratio > 1)
	{
		free_split(tokens);
		ft_err("Ambient ratio must be in [0.0,1.0]!", &data->gc_root, 1);
	}
	if (get_color(tokens[2], &data->scene.amb.color))
	{
		free_split(tokens);
		ft_err("Invalid ambient color!", &data->gc_root, 1);
	}
}

void	parse_ambient(t_data *data, char **tokens)
{
	validate_ambient_tokens(data, tokens);
	validate_ambient_values(data, tokens);
	data->scene.amb.is_set = true;
}
