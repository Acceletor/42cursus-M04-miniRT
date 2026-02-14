/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:02:33 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:02:34 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	validate_camera_tokens(t_data *data, char **tokens)
{
	if (!tokens || split_len(tokens) != 4)
	{
		free_split(tokens);
		ft_err("invalid camera!", &data->gc_root, 1);
	}
	if (data->scene.cam.is_set == true)
	{
		free_split(tokens);
		ft_err("Too many camera!", &data->gc_root, 1);
	}
}

void	validate_camera_vectors(t_data *data, char **tokens)
{
	if (has_invalid_input(tokens[1]) || has_invalid_input(tokens[2])
		|| has_invalid_input(tokens[3]))
	{
		free_split(tokens);
		ft_err("Camera has invalid input!", &data->gc_root, 1);
	}
	if (get_vec(tokens[1], &data->scene.cam.pos) || get_vec(tokens[2],
			&data->scene.cam.dir))
	{
		free_split(tokens);
		ft_err("Invalid Camera Vector!", &data->gc_root, 1);
	}
	if (data->scene.cam.dir.x > 1 || data->scene.cam.dir.y > 1
		|| data->scene.cam.dir.z > 1 || data->scene.cam.dir.x < -1
		|| data->scene.cam.dir.y < -1 || data->scene.cam.dir.z < -1
		|| (data->scene.cam.dir.x == 0 && data->scene.cam.dir.y == 0
			&& data->scene.cam.dir.z == 0))
	{
		free_split(tokens);
		ft_err("Invalid Camera orientation!", &data->gc_root, 1);
	}
	data->scene.cam.dir = vec_normalize(data->scene.cam.dir);
}

void	validate_camera_fov(t_data *data, char **tokens)
{
	data->scene.cam.fov = ft_atod(tokens[3]);
	if (data->scene.cam.fov < 0 || data->scene.cam.fov > 180)
	{
		free_split(tokens);
		ft_err("Camera's FOV must be in [0,180]", &data->gc_root, 1);
	}
}

void	parse_camera(t_data *data, char **tokens)
{
	validate_camera_tokens(data, tokens);
	validate_camera_vectors(data, tokens);
	validate_camera_fov(data, tokens);
	data->scene.cam.is_set = true;
}
