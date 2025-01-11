/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlehmeye <nlehmeye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:02:13 by nlehmeye          #+#    #+#             */
/*   Updated: 2025/01/11 16:19:16 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//  -- CAST_RAY() --
t_intersect	cast_ray(t_list *objs, t_ray ray)
{
	t_intersect	intersection;
	t_intersect	temp_intersect;

	ft_bzero(&intersection, sizeof(intersection));
	while (objs != NULL)
	{
		if (((t_obj *)objs->content)->id == PLANE)
			temp_intersect = cast_ray_plane(((t_obj *)objs->content), ray);
		else if (((t_obj *)objs->content)->id == SPHERE)
			temp_intersect = cast_ray_sphere(((t_obj *)objs->content), ray);
		else if (((t_obj *)objs->content)->id == CYLINDER)
			temp_intersect = cast_ray_cylinder(((t_obj *)objs->content), ray);
		if (temp_intersect.cam_dist < intersection.cam_dist)
			intersection = temp_intersect;
		objs = objs->next;
	}
	return (intersection);
}
//  -- CAST_RAY_SPHERE() --

t_intersect	cast_ray_sphere(t_obj *obj, t_ray ray)
{
	t_intersect	intersection;

	double	t;

	return ((t_intersect){.obj = NULL});
}
t_point	find_intersect_point(double t, t_ray ray)
{
	t_point	point;


	return (point);
}

t_intersect	solve_quadratic(t_obj *obj, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	t;

	a = vec3_dot(ray.dir, ray.dir);
	b = 2 * vec3_dot(something, ray.dir);
	c = ;
	t = 
	return (t);
}
// find closest point of object, not past [max distance]
// params:
//   t obj object (the type of obj) to check intersects
//   angle direction of ray (normalised)
//   max distance (double, infinity if no max dist)
// returns: closest intersection point, as t_intersect datatype


//  -- CAST_RAY_PLANE() --
t_intersect	cast_ray_plane(t_obj *obj, t_ray ray)
{
	//t_intersect	intersection;
	(void)obj, (void)ray;

	return ((t_intersect){.obj = NULL});
}
// find closest point of object, not past [max distance]
// params:
//   t obj object (the type of obj) to check intersects
//   angle direction of ray (normalised)
//   max distance (double, infinity if no max dist)
// returns: closest intersection point, as t_intersect datatype

//typedef struct s_intersect
// {
// 	t_point	point;
// 	t_obj	*obj;
// 	t_angle	normal;
// 	double	cam_dist;
// }	t_intersect;
