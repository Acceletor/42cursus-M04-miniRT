#include "../include/minirt.h"

void	init_scene(t_data *data)
{
	data->scene.objs = NULL;
	data->scene.light = NULL;
	data->scene.amb.is_set = false;
	data->scene.amb.ratio = 0.0;
	data->scene.cam.is_set = false;
}

t_camera	set_camera(t_scene *sc)
{
	t_camera	cam;
	t_vec		world_up;

	cam.pos = sc->cam.pos;
	cam.aspect = (double)WIDTH / (double)HEIGHT;
	cam.theta = sc->cam.fov * M_PI / 180.0;    // horizontal FOV
	cam.vp_width = 2.0 * tan(cam.theta / 2.0); // distance = 1
	cam.vp_height = cam.vp_width / cam.aspect;
	cam.forward = vec_normalize(sc->cam.dir);
	world_up = (t_vec){0, 1, 0}; // +Y
	if (fabs(cam.forward.x) < EPSILON && fabs(cam.forward.z) < EPSILON)
		world_up = (t_vec){0, 0, 1}; // +Z
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
