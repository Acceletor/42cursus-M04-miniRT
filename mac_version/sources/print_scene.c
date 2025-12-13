#include "../include/minirt.h"

void	print_vec(char *label, t_vec v)
{
	printf("%s(%.2f, %.2f, %.2f)\n", label, v.x, v.y, v.z);
}

void	print_ambient(t_amb *amb)
{
	if (!amb->is_set)
	{
		printf("Ambient: not set\n");
		return ;
	}
	printf("=== Ambient ===\n");
	printf("ratio: %.3f\n", amb->ratio);
	print_vec("color: ", amb->color);
}

void	print_camera(t_cam *cam)
{
	if (!cam->is_set)
	{
		printf("Camera: not set\n");
		return ;
	}
	printf("=== Camera ===\n");
	print_vec("pos:   ", cam->pos);
	print_vec("dir:   ", cam->dir);
	printf("fov: %.2f\n", cam->fov);
}

void	print_lights_and_objs(t_scene *sc)
{
	t_light	*li;
	t_objs	*ob;
	int		i;

	li = sc->light;
	i = 0;
	printf("=== Lights ===\n");
	if (!li)
		printf("none\n");
	while (li)
	{
		printf("Light #%d\n", i++);
		print_vec("  pos:   ", li->pos);
		printf("  ratio: %.3f\n", li->ratio);
		print_vec("  color: ", li->color);
		li = li->next;
	}
	ob = sc->objs;
	i = 0;
	printf("=== Objects ===\n");
	if (!ob)
		printf("none\n");
	while (ob)
	{
		printf("Object #%d: ", i++);
		if (ob->type == OBJ_SPHERE)
		{
			printf("Sphere\n");
			print_vec("  center:  ", ((t_sphere *)ob->data)->center);
			printf("  diam:    %.3f\n",
				((t_sphere *)ob->data)->diameter);
			print_vec("  color:   ",
				((t_sphere *)ob->data)->color);
		}
		else if (ob->type == OBJ_PLANE)
        {
			printf("Plane\n");
            print_vec("  point:  ", ((t_plane *)ob->data)->point);
            print_vec("  normal:  ",
				((t_plane *)ob->data)->normal);
            print_vec("  color:   ",
				((t_plane *)ob->data)->color);
        }
		else if (ob->type == OBJ_CYLINDER)
			printf("Cylinder (no print data yet)\n");
		ob = ob->next;
	}
}

void	print_scene(t_data *data)
{
	printf("===== SCENE DUMP =====\n");
	print_ambient(&data->scene.amb);
	printf("\n");
	print_camera(&data->scene.cam);
	printf("\n");
	print_lights_and_objs(&data->scene);
	printf("\n");
}
