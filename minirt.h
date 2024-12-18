/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:16:39 by njackson          #+#    #+#             */
/*   Updated: 2024/12/18 13:22:04 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

// some define crap, don't worry about this
# ifdef LINUX
#  define K_ESCAPE 0xff1b

#  define DESTROY_DISPLAY 1
#  define RESIZABLE 1

# else
#  define K_ESCAPE 0x35

void	mlx_destroy_display(void *mlx);
#  define DESTROY_DISPLAY 0
#  define RESIZABLE 0
# endif

// colour, stored as 3 values from 0-255
// it may be useful in future to have a vector type colour struct as well
typedef struct s_colour
{
	int	red;
	int	blue;
	int	green;
}	t_colour;

// a basic vector type
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

// typedefs so we can specify what a vector is being used for
typedef t_vec3	t_pos;
typedef t_vec3	t_angle;
typedef t_vec3	t_point;

// the ambient light of a scene
typedef struct s_alight
{
	double	ratio;
	t_colour	colour;
}	t_alight;

// a spot light, or just a light
typedef struct s_light
{
	t_pos	pos;
	double	ratio;
	t_colour	colour;
}	t_light;

// the camera :)
// angle is the direction in which the comera faces. I'm not set on this name,
//  feel free to rename it
// fov stands for field of view, which is the horizontal angle for the camera
typedef struct s_cam
{
	t_pos	pos;
	t_pos	angle;
	int		fov;
	double	psin;
	double	pcos;
	double	ysin;
	double	ycos;
	double	rect_dist;
}	t_cam;

// an enum for defining what type of object is stored in the struct below
typedef enum e_obj_id
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_obj_id;

// the default object struct; this could be 3 different structs, but I think
//  it'll make things slightly easier if we store it as one
// note that diameter is unused for a plane, angle is unused for a sphere, and
// height is unused for both
typedef struct s_obj
{
	t_obj_id	id;
	t_pos		pos;
	t_colour	colour;
	t_angle		angle;
	double		diameter;
	double		height;
}	t_obj;

// for object type specific functions, it might be useful to refer to the
// objects by their specific types, rather than a generalized object
typedef t_obj	t_plane;
typedef t_obj	t_sphere;
typedef t_obj	t_cylinder;

typedef struct s_scene
{
	t_alight	alight;
	// below may change later to a linked list
	t_cam		cam;
	t_light		light;
	t_list		*objs;
}	t_scene;

// all the useful mlx image data
typedef struct s_image
{
	void			*img;
	unsigned int	*imgdat;
	int				height;
	int				width;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}	t_image;

// a collection of all the mlx data.
typedef struct s_mlx
{
	void	*mlxptr;
	void	*winptr;
	t_image	img;
}	t_mlx;

// a complete collection of all the common information that will need to be
// passed around. When creating the data at the start, you'll only have the
// struct you're adding to
typedef struct s_mrt_dat
{
	t_scene	scene;
	t_mlx	mlx;
}	t_mrt_dat;

typedef struct s_intersect
{
	t_point	point;
	t_obj	*obj;
	t_angle	normal;
	double	cam_dist;
}	t_intersect;

// camera functions
void	init_camera(t_cam *cam);
t_colour	raytrace_pixel(t_mrt_dat *dat, int x, int y);

// vector math functions -- detailed in doc
double	vec3_dot_product(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_cross_product(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_inverse(t_vec3 vec);
t_vec3	vec3_reflect(t_vec3 vec, t_vec3 reflect);
t_vec3	vec3_normalise(t_vec3 vec);

// mlx management functions
int		get_mlx_dat(t_mrt_dat *dat);
int		cleanup_mlx(t_mlx *mlx);
int		new_image(void *mlxptr, t_image *image, int width, int height);
void	get_all_pixels(t_mrt_dat *dat,
			t_colour (*pixel_func)(t_mrt_dat *, int, int));
int		key_hook(int key, t_mrt_dat *dat);

//  ** main.c ** //
int 	test_main(void);
void	free_list_obj(t_list *objs);

//  ** parse_input.c ** //
int		parse_input(const char *file, t_scene *scene);
int		id_assign(char *line, t_scene *scene);
void	id_assign_assist(char **elements, t_scene *scene, int *err);
int		count_array_rows(void **arr);

// ** assign_ACL.c ** //
int		assign_a(char **elements, t_scene *scene);
int		assign_c(char **elements, t_scene *scene);
int		assign_l(char **elements, t_scene *scene);
int		assign_vector(char *elementinfo, t_vec3 *vector);
int		assign_colour(char *elementinfo, t_colour *rgb);

// ** assign_obj.c ** //
int		assign_pl(char **elements, t_scene *scene);
int		assign_sp(char **elements, t_scene *scene);
int		assign_cy(char **elements, t_scene *scene);
void	assign_cy_assist(char **elements, t_obj *cylinder, int *err);
double	assign_obj_assist(char *element, int *err);


// ** check_elements.c ** //
int		check_unit(double ratio);
int		check_colour_range(t_colour rgb);
int		check_positive(double obj_dimensions);
int		check_fov(int fov);
int		check_sym_unit(t_vec3 angle);

#endif //MINIRT_H
