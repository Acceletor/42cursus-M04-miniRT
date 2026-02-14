#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
}						t_mlx;

typedef struct s_vec
{
	double				x;
	double				y;
	double				z;
}						t_vec;

typedef struct s_image // mlx image buffer
{
	void *img;
	void *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}						t_image;

typedef struct s_ray
{
	t_vec				origin;
	t_vec				dir;
}						t_ray;

typedef struct s_camera
{
	t_vec				pos;
	t_vec				forward;
	t_vec				right;
	t_vec				up;
	double				aspect;
	double theta; // horizontal FOV (radian)
	double				vp_width;
	double				vp_height;
}						t_camera;

typedef struct s_renderer
{
	t_mlx				mlx;
	t_image				img;
	int					x;
	int					y;
	double				sx;
	double				sy;
	t_camera			cam;
	t_ray				ray;
	t_vec				ray_col;
}						t_renderer;

// P(t) = ray.origin + ray.dir * t

typedef struct s_inter
{
	double t;  // distance along the ray
	t_vec hit; // the exact 3D point where the ray touches the object
	t_vec				norm;
	t_vec				color;
}						t_inter;

/* ====== Global element (appear once)======= */
typedef struct s_amb
{
	bool				is_set;
	double				ratio;
	t_vec				color;
}						t_amb;

typedef struct s_cam
{
	bool				is_set;
	t_vec				pos;
	t_vec dir;  // [-1, 1]
	double fov; // [0, 180]
}						t_cam;

typedef struct s_light // at least 1
{
	t_vec pos;
	double ratio;
	t_vec color;
	struct s_light *next;
}						t_light;

/* ====== Objects ======= */

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_TUBE,
	OBJ_CONE,
	OBJ_CIRCLE
}						t_obj_type;

typedef struct s_objs
{
	t_obj_type			type;
	void				*data;
	struct s_objs		*next;
}						t_objs;

typedef struct s_sphere
{
	t_vec				center;
	double				diameter;
	t_vec				color;
}						t_sphere;

typedef struct s_plane
{
	t_vec				point;
	t_vec				normal;
	t_vec				color;
}						t_plane;

typedef struct s_cylinder
{
	t_vec				center;
	t_vec				normal;
	double				diameter;
	double				height;
	t_vec				color;
}						t_cylinder;

typedef struct s_circle
{
	t_vec				center;
	t_vec				normal;
	double				diameter;
	t_vec				color;
}						t_circle;

/* ====== Containers ======= */

typedef struct s_scene
{
	t_vec				col;
	t_cam				cam;
	t_light				*light;
	t_amb				amb;
	t_objs				*objs;
}						t_scene;

typedef struct s_collector
{
	void				*adr;
	struct s_collector	*next;
}						t_collector;

typedef struct s_data
{
	t_collector			*gc_root;
	t_scene				scene;
	int					fd;
	t_renderer			renderer;
}						t_data;

// sp
typedef struct s_sp_quad
{
	double				r;
	t_vec				oc;
	double				a;
	double				b;
	double				c;
	double				disc;
	double				sd;
	double				t1;
	double				t2;
}						t_sp_quad;

// cy
typedef struct s_cy_quad
{
	double				r;
	t_vec				oc;
	t_vec				d_perp;
	t_vec				oc_perp;
	double				a;
	double				b;
	double				c;
	double				disc;
	double				sd;
	double				t1;
	double				t2;
}						t_cy_quad;

typedef struct s_cy_hits
{
	double				t_side;
	double				t_top;
	double				t_bot;
}						t_cy_hits;

typedef struct s_cy_update
{
	t_cy_hits			hits;
	t_vec				axis;
	t_cylinder			*cy;
	t_ray				*ray;
}						t_cy_update;

#endif