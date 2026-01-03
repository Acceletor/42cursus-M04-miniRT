#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 800
# define HEIGHT 600
# define EPSILON 0.000001
# define WINDOW_NAME "MiniRT"

# include <stdlib.h>
# include <fcntl.h> 
# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include "../libmlx/macos/mlx.h"
# include "../libft/get_next_line.h"
# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include "structs.h"

// core_error.c
void ft_err(char *str, t_collector **g_root, int err);

//core_util.c
int invalid_file(int argc, char **argv, t_data *data);
void free_split(char **tokens);
double	ft_atod(const char *s);
int split_len(char **tokens);

// core_gc.c (manual garbage collector)
void gc_free_all(t_collector **g_root);
t_collector *new_node(void *adr);
int gc_append_adr(t_collector **g_root, void *adr);
void * gc_malloc(t_collector **g_root ,size_t size);

//core_init.c
void init_scene(t_data *data);
t_camera set_camera(t_scene *sc);
void image_init(t_renderer *info);


//core_parse.c

void parse_identifier(char* id, char**tokens, t_data *data);
void trim_line_newline(char *s);
int parse(t_data *data);

// parse_utils.c
t_vec	make_vec(double x, double y, double z);
int get_vec(char *str, t_vec *out);
int get_color(char *str, t_vec *out);
t_objs *alloc_object(t_obj_type type, t_collector **gc_root);
void	add_object_to_scene(t_scene *scene, t_objs *new);

// parse_input_validator.c
int is_invalid_double(char *s);
int is_invalid_vector(char *s);
int has_invalid_input(char *token);

// parse_ambient.c
void	validate_ambient_tokens(t_data *data, char **tokens);
void	validate_ambient_values(t_data *data, char **tokens);
void	parse_ambient(t_data *data, char **tokens);

//parse_camera.c
void	validate_camera_tokens(t_data *data, char **tokens);
void	validate_camera_vectors(t_data *data, char **tokens);
void	validate_camera_fov(t_data *data, char **tokens);
void parse_camera(t_data *data, char **tokens);

//parse_light.c
void	validate_light_tokens(t_data *data, char **token);
t_light	*alloc_light(t_data *data, char **token);
void	set_light_params(t_data *data, t_light *new, char **token);
void	add_light_to_scene(t_scene *scene, t_light *new);
void parse_light(t_data *data, char **token);

//parse_sphere.c
void parse_sphere(t_data *data, char **tokens);

//parse_plane.c
void parse_plane(t_data *data, char **tokens);

//parse_cylinder.c
void parse_cylinder(t_data *data, char **tokens);

//print_scene.c
void	print_vec(char *label, t_vec v);
void	print_ambient(t_amb *amb);
void	print_camera(t_cam *cam);
void	print_lights_and_objs(t_scene *sc);
void	print_scene(t_data *data);

// vector_op.c
t_vec vec_cross(t_vec u, t_vec v);
t_vec vec_normalize(t_vec v);
double dot_vec(t_vec a, t_vec b);
t_vec normalize_color(t_vec rgb);

// vector_op2.c
t_vec sub_vec(t_vec a, t_vec b);
t_vec add_vec(t_vec u, t_vec v);
t_vec mult_vec(t_vec v, double a);

// rendering.c
void draw(t_renderer *info, t_scene *sc);
void rendering(t_scene *sc);

// ray_cal.c
t_inter scene_inter(t_ray *ray, t_scene *sc);
t_vec   ray_color(t_ray *ray, t_scene *sc);
t_ray ray_primary(t_camera *cam, double sx, double sy);

//hit_object_update.c
t_inter hit_sphere_update(t_inter best, t_objs *obj, t_ray *ray);

// intersection.c
double	get_smallest_positive(double t1, double t2);
int sphere_intersect(t_ray *ray, t_sphere *sp ,double *t_hit);

// covert_to_rgb.c
int to_byte(double x);
int create_rgb(int r, int g, int b);
int vec_to_rgb(t_vec c);




#endif