#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 800
# define HEIGHT 600
# define EPSILON 0.000001
# define WINDOW_NAME "MiniRT"

# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

// core_error.c
void		ft_err(char *str, t_collector **g_root, int err);

// core_util.c
int			invalid_file(int argc, char **argv, t_data *data);
void		free_split(char **tokens);
double		ft_atod(const char *s);
int			split_len(char **tokens);

// core_gc.c (manual garbage collector)
void		gc_free_all(t_collector **g_root);
t_collector	*new_node(void *adr);
int			gc_append_adr(t_collector **g_root, void *adr);
void		*gc_malloc(t_collector **g_root, size_t size);

// core_init.c
void		init_scene(t_data *data);
t_camera	set_camera(t_scene *sc);
void		image_init(t_renderer *info);

// core_parse.c
void		parse_identifier(char *id, char **tokens, t_data *data);
void		trim_line_newline(char *s);
int			parse(t_data *data);

// parse_utils.c
t_vec		make_vec(double x, double y, double z);
int			get_vec(char *str, t_vec *out);
int			get_color(char *str, t_vec *out);
t_objs		*alloc_object(t_obj_type type, t_collector **gc_root);
void		add_object_to_scene(t_scene *scene, t_objs *new);

// parse_input_validator.c
int			is_invalid_double(char *s);
int			is_invalid_vector(char *s);
int			has_invalid_input(char *token);
int     is_out_of_bounds(t_vec *v);

// parse_ambient.c
void		validate_ambient_tokens(t_data *data, char **tokens);
void		validate_ambient_values(t_data *data, char **tokens);
void		parse_ambient(t_data *data, char **tokens);

// parse_camera.c
void		validate_camera_tokens(t_data *data, char **tokens);
void		validate_camera_vectors(t_data *data, char **tokens);
void		validate_camera_fov(t_data *data, char **tokens);
void		parse_camera(t_data *data, char **tokens);

// parse_light.c
void		validate_light_tokens(t_data *data, char **token);
t_light		*alloc_light(t_data *data, char **token);
void		set_light_params(t_data *data, t_light *new, char **token);
void		add_light_to_scene(t_scene *scene, t_light *new);
void		parse_light(t_data *data, char **token);

// parse_sphere.c
void		parse_sphere(t_data *data, char **tokens);

// parse_plane.c
void		parse_plane(t_data *data, char **tokens);

// parse_cylinder.c
void		parse_cylinder(t_data *data, char **tokens);

// parse_tube.c
void	parse_tube(t_data *data, char **tokens);

// parse_cone.c
void	parse_cone(t_data *data, char **tokens);

// parse_circle.c
void	parse_circle(t_data *data, char **tokens);

// print_scene.c
void		print_vec(char *label, t_vec v);
void		print_ambient(t_amb *amb);
void		print_camera(t_cam *cam);
void		print_lights_and_objs(t_scene *sc);
void		print_scene(t_data *data);

// vector_op.c
t_vec		vec_cross(t_vec u, t_vec v);
t_vec		vec_normalize(t_vec v);
double		dot_vec(t_vec a, t_vec b);
t_vec		normalize_color(t_vec rgb);

// vector_op2.c
t_vec		sub_vec(t_vec a, t_vec b);
t_vec		add_vec(t_vec u, t_vec v);
t_vec		mult_vec(t_vec v, double a);
t_vec		hadamard(t_vec a, t_vec b);

// core_render.c
void		my_mlx_pixel_put(t_image *img, int x, int y, int color);
int			handle_key(int keycode, void *param);
void		draw(t_renderer *info, t_scene *sc);
void		rendering(t_data *data);
int			clean_exit(t_data *data);

// ren_ray_cal.c
t_inter		scene_inter(t_ray *ray, t_scene *sc);
t_vec		ray_color(t_ray *ray, t_scene *sc);
t_ray		ray_primary(t_camera *cam, double sx, double sy);

// ren_color_cal.c
t_vec		shade_hit(t_scene *sc, t_inter inter);

// ren_sphere.c
t_inter		hit_sphere_update(t_inter best, t_objs *obj, t_ray *ray);

// ren_plane.c
t_inter		hit_plane_update(t_inter best, t_objs *obj, t_ray *ray);

// ren_cylinder.c
t_inter		hit_cylinder_update(t_inter best, t_objs *obj, t_ray *ray);
t_inter	hit_tube_update(t_inter best, t_objs *obj, t_ray *ray);

// ren_cylinder_side.c
int			cy_side_hit(t_ray *ray, t_cylinder *cy, t_vec axis, double *t_side);
int	    cy_infinite_hit(t_ray *ray, t_cylinder *cy, t_vec axis, double *t_side);

// ren_circle.c
int	circle_intersection(t_ray *ray, t_circle *ci, double *t_hit);
t_inter	hit_circle_update(t_inter best, t_objs *obj, t_ray *ray);

// ren_cone.c
t_inter	hit_cone_update(t_inter best, t_objs *obj, t_ray *ray);

// ren_cone_side.c
int	co_side_hit(t_ray *ray, t_cylinder *co, t_vec axis, double *t_side);

// ren_utils.c
double		smallest_positive(double t1, double t2);
double	smallest_positive_within_cy(t_ray *ray, t_cylinder *cy, t_vec axis, t_cy_quad	q);
double	smallest_positive_within_co(t_ray *ray, t_cylinder *co, t_vec axis, t_cy_quad	q);

// covert_to_rgb.c
int			to_byte(double x);
int			create_rgb(int r, int g, int b);
int			vec_to_rgb(t_vec c);
t_vec		clamp01(t_vec c);


#endif