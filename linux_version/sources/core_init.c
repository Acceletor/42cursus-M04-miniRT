/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:03:30 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:20:12 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	init_scene(t_data *data)
{
	data->scene.objs = NULL;
	data->scene.light = NULL;
	data->scene.amb.is_set = false;
	data->scene.amb.ratio = 0.0;
	data->scene.cam.is_set = false;
}

/*
Initializes the viewport
Converts degrees FOV (sc->cam.fov) to radians (cam.theta)
M_PI - Math PI
Based on theta calculates the vp_width.
  Flattening of the viewport. From a 'part of a circle' to a triangle.
  Theta is 'the angle of the viewport triangle'.
  by dividing it by 2 I get a right angle triangle.
  Assuming distance from origin to 'screen' is 1,
	tan can be used to calculate the 'screen' side of the triangle (half-width).
   tan = opposite / adjacent(1)
vp_height calculated with respect to aspect.
		.
		/|\<-theta/2
		/ | \
	/  |  \
   /   |<-1\
  /    |    \
 /_____|_____\
			^
			vp_width/2

Normalizes the camera direction vector.
Grounds direction to +Y axis.
Lock prevention - if cam.dir only on Y axis, change ground to +Z.

Initializes relative (from cam.dir) direction vectors (up & right).
forward perpendicular to up perpendicular to right
*/
t_camera	set_camera(t_scene *sc)
{
	t_camera	cam;
	t_vec		world_up;

	cam.pos = sc->cam.pos;
	cam.aspect = (double)WIDTH / (double)HEIGHT;
	cam.theta = sc->cam.fov * M_PI / 180.0;
	cam.vp_width = 2.0 * tan(cam.theta / 2.0);
	cam.vp_height = cam.vp_width / cam.aspect;
	cam.forward = vec_normalize(sc->cam.dir);
	world_up = (t_vec){0, 1, 0};
	if (fabs(cam.forward.x) < EPSILON && fabs(cam.forward.z) < EPSILON)
		world_up = (t_vec){0, 0, 1};
	cam.right = vec_normalize(vec_cross(cam.forward, world_up));
	cam.up = vec_normalize(vec_cross(cam.right, cam.forward));
	return (cam);
}

void	image_init(t_renderer *info)
{
	info->mlx.mlx = mlx_init();
	info->mlx.win = mlx_new_window(info->mlx.mlx, WIDTH, HEIGHT, WINDOW_NAME);
	info->img.img = mlx_new_image(info->mlx.mlx, WIDTH, HEIGHT);
	info->img.addr = mlx_get_data_addr(info->img.img, &info->img.bits_per_pixel,
			&info->img.line_length, &info->img.endian);
}
