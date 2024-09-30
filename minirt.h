/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:16:39 by njackson          #+#    #+#             */
/*   Updated: 2024/09/30 17:27:23 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"

// some define crap, don't worry about this
# ifdef LINUX
#  define DESTROY_DISPLAY 1
#  define RESIZABLE 1
# else
void	mlx_destroy_display(void *mlx);
#  define DESTROY_DISPLAY 0
#  define RESIZABLE 0
# endif

// color, stored as 3 values from 0-255
// it may be useful in future to have a vector type color struct as well
typedef struct s_color
{
	int	red;
	int	blue;
	int	green;
}	t_color;

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
	t_color	color;
}	t_alight;

// a spot light, or just a light
typedef struct s_slight
{
	t_pos	pos;
	double	ratio;
	t_color	color;
}	t_slight;

// the camera :)
// angle is the direction in which the comera faces. I'm not set on this name,
//  feel free to rename it
// fov stands for field of view, which is the horizontal angle for the camera
typedef struct s_cam
{
	t_pos	pos;
	t_pos	angle;
	int		fov;
}	t_cam;

// an enum for defining what type of object is stored in the struct below
typedef enum e_obj_id
{
	SPHERE,
	PLANE,
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
	t_color		color;
	t_angle		angle;
	double		diameter;
	double		height;
}	t_obj;

// for object type specific functions, it might be useful to refer to the
// objects by their specific types, rather than a generalized object
typedef t_obj	t_plane;
typedef t_obj	t_sphere;
typedef t_obj	t_cylinder;

/*
IN LIBFT t_list MUST BE DEFINED AS
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
THIS WILL BREAK OTHERWISE
don't think about this too hard though

note, I may remove this later, changing all references to it to use explicit
casts
*/
typedef struct s_obj_list
{
	t_obj				*content;
	struct s_obj_list	*next;
}	t_obj_list;

// a collection of all the parts of the scene
typedef struct s_scene
{
	t_alight	alight;
	// below may change later to a linked list
	t_slight	slight;
	t_cam		cam;
	t_obj_list	*objs;
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

int		get_mlx_dat(t_mlx *mlx);
int		cleanup_mlx(t_mlx *mlx);
int		new_image(void *mlxptr, t_image *image, int width, int height);
void	get_all_pixels(t_mrt_dat *dat,
			t_color (*pixel_func)(t_mrt_dat *, int, int));

#endif //MINIRT_H
