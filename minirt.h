/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:16:39 by njackson          #+#    #+#             */
/*   Updated: 2024/09/25 12:54:16 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"

typedef struct s_color
{
	int	red;
	int	blue;
	int	green;
}	t_color;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3	t_pos;
typedef t_vec3	t_angle;
typedef t_vec3	t_point;

typedef struct s_alight
{
	double	ratio;
	t_color	color;
}	t_alight;

typedef struct s_slight
{
	t_pos	pos;
	double	ratio;
	t_color	color;
}	t_slight;

typedef struct s_cam
{
	t_pos	pos;
	t_pos	angle;
	int		fov;
}	t_cam;

typedef enum e_obj_id
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_id;

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

/*
IN LIBFT t_list MUST BE DEFINED AS
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}
THIS WILL BREAK OTHERWISE
*/
typedef struct s_obj_list
{
	t_obj				*content;
	struct s_obj_list	*next;
}	t_obj_list;

typedef struct s_scene
{
	t_alight	alight;
	// below may change later to a linked list
	t_slight	slight;
	t_cam		cam;
	t_obj_list	objs;
}	t_scene;

#endif //MINIRT_H
