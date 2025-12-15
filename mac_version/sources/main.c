#include "../include/minirt.h"

t_vec vec_cross(t_vec u, t_vec v)
{
    t_vec w;
    w.x = (u.y * v.z) - (u.z * v.y);
    w.y = (u.z * v.x) - (u.x * v.z);
	w.z = (u.x * v.y) - (u.y * v.x);
    return (w);
}

t_vec vec_normalize(t_vec v)
{
    t_vec normalized;
    double len;

    len = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    if (len < EPSILON)
        return ((t_vec){0,0,0});
    normalized.x = v.x / len;
    normalized.y = v.y / len;
    normalized.z = v.z / len;

    return (normalized);
}

t_camera set_camera(t_scene *sc)
{
    t_camera cam;
    t_vec world_up;

    cam.pos = sc->cam.pos;
    cam.aspect = (double)WIDTH / (double)HEIGHT;
    cam.theta = sc->cam.fov * M_PI / 180.0; // horizontal FOV
    cam.vp_width = 2.0 * tan(cam.theta/2.0); // distance = 1
    cam.vp_height = cam.vp_width / cam.aspect;
    cam.forward = vec_normalize(sc->cam.dir);
    world_up = (t_vec){0, 1, 0};
    cam.right = vec_normalize(vec_cross(cam.forward, world_up));
    cam.up =  vec_cross(cam.right, cam.forward);
    return (cam);
}

void rendering(t_scene *sc)
{
    t_renderer info;

    info.cam = set_camera(sc);
    
}


int main(int argc, char **argv)
{
    t_data data;

    data.gc_root = NULL;
    data.fd = -1;
    if (invalid_file(argc, argv, &data))
        ft_err("Incorrect argument: ./miniRT file_name.rt", &data.gc_root, 1);
    init_scene(&data);
    parse(&data);
    print_scene(&data);
    rendering(&data.scene);

    // .......program logic.......
    
    gc_free_all(&data.gc_root);
    // close(fd)
    return 0;
}